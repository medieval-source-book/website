<?php

/**
 * @file
 * MAYO plugin sub-system.
 */

/**
 * Find and return all plugins.
 *
 * This will search all base themes and the active theme for "plugins" in their
 * info files, and return all plugins directories.
 * MAYO page layouts uses:
 * - "plugins[page_layout][layout] = layouts/core"
 *
 * @param $theme_name, usually the active theme.
 */
function mayo_get_plugins($theme_name) {
  $plugins = drupal_static(__FUNCTION__, array());
  if (empty($plugins)) {
      $plugins_list = array();
      $themes_info = mayo_get_info_trail($theme_name);
      // Look for and get all the plugins
      if (!empty($themes_info)) {
        foreach ($themes_info as $this_theme => $theme_info) {
          foreach ($theme_info as $info) {
            if (array_key_exists('plugins', $info)) {
              foreach ($info['plugins'] as $plugin_type => $types) {
                $plugins_list[$this_theme][$plugin_type] = $types;
              }
            }
          }
        }
        $plugins = $plugins_list;
      }
  }
  return $plugins;
}

/**
 * Return the paths to all plugin providers plugin directories, this usually
 * means themes - both base themes and sub-themes that include plugin directory
 * declarations in their info files.
 *
 * @param $theme_name, ususally the active theme.
 */
function mayo_get_plugins_paths($theme_name) {
  $provider_paths = array();
  $plugins_list = mayo_get_plugins($theme_name);

  foreach ($plugins_list as $plugin_provider => $provider) {
    foreach ($provider as $plugin_type => $types) {
      foreach ($types as $type => $path) {
        $provider_path = drupal_get_path('theme', $plugin_provider) . '/' . $path;
        $provider_paths[$plugin_provider][$plugin_type][$type] = $provider_path;
      }
    }
  }

  return $provider_paths;
}

/**
 * Returns all files for plugins of a particular type.
 * This is called from mayo_load_plugins(), cannot be cached else it will return
 * stale data at some point.
 *
 * @param $theme_name
 */
function mayo_get_plugins_files($theme_name) {
  $plugins_files = array();
  $plugins_list = mayo_get_plugins($theme_name);

  $extension = 'inc';
  foreach ($plugins_list as $plugin_provider => $provider) {
    foreach ($provider as $plugin_type => $types) {
      foreach ($types as $type => $path) {
        $provider_path = drupal_get_path('theme', $plugin_provider) . '/' . $path;
        $plugins_files[$plugin_provider][$plugin_type][$type] = file_scan_directory($provider_path, '/\.' . $extension . '$/', array('key' => 'name'));
      }
    }
  }

  return $plugins_files;
}

/**
 * Extract plugin data structures.
 *
 * In essence what this does is return the data strutures (arrays) for all
 * plugins of a particular type. MAYO only uses the "page_layout" type.
 * This is hard to cache because it takes the
 * $plugin_type parameter, so everything else that calls this is heavily cached
 * instead. It does support an "everything else" plugin type, whatever that is.
 *
 * @param $theme_name, usually the active theme.
 * @param $plugin_type, the plugin type you need to return, usually one of
 * "panels" or "page_layout".
 */
function mayo_load_plugins($theme_name, $plugin_type) {
  $plugin_data_structures = array();
  $plugins_list = mayo_get_plugins_files($theme_name);
  $plugins_array = array();
  foreach ($plugins_list as $plugin_provider => $plugin_types) {
    $plugin_providers[] = $plugin_provider;
    foreach ($plugin_types as $type => $plugins) {
      if ($type === $plugin_type) {
        foreach ($plugins as $ptypes => $plugin) {
          $plugins_array[$plugin_provider][$type] = $plugin;
        }
      }
    }
  }
  $plugin_files = array();
  foreach ($plugins_array as $provider => $types) {
    foreach ($types as $key => $value) {
      $plugin_files = array_merge_recursive($plugin_files, $value);
    }
  }

  foreach ($plugin_files as $file_data) {

    include_once(DRUPAL_ROOT . '/' . $file_data->uri);

    // page_layout
    if ($plugin_type === 'page_layout') {
      $identifier = $file_data->name;
      $page_layout_function = $identifier;
      if (function_exists($page_layout_function)) {
        $plugin_data_structures[] = $page_layout_function();
      }
    }

    // everything else
    elseif ($plugin_type !== 'panels' && $plugin_type !== 'page_layout') {
      $identifier = $file_data->name;
      $function = $identifier;
      if (function_exists($function)) {
        $plugin_data_structures[] = $function();
      }
      else {
        drupal_set_message(t('You defined an existing plugin type but no functions exists that match. If you are using Panels then you must use the "function method" in your plugins.'), 'error');
      }
    }
  }

  if (empty($plugin_data_structures)) {
    return;
  }
  return $plugin_data_structures;
}

/**
 * Return Page layout data structures.
 * This returns the full data structures for all page layout plugins. Because
 * this can be a lot of data and appears to be computationally expensive to get
 * it is cached in the cache table.
 *
 * @param $theme_name, the active theme.
 */
function page_layouts_data_structure($theme_name = NULL) {
  // Use the passed in theme_name, else grab it from the global variable
  if ($theme_name == NULL) {
    global $theme_key;
    $theme_name = $theme_key;
  }

  $page_data_structure = drupal_static(__FUNCTION__, array());
  if (empty($page_data_structure)) {
      $data_structure = mayo_load_plugins($theme_name, $plugin_type = 'page_layout');
      foreach ($data_structure as $plugin => $datum) {
        foreach ($datum as $method => $layout) {
          $page_data_structure[$method] = $layout;
        }
      }
  }
  return $page_data_structure;
}

/**
 * Return option arrays for forms.
 * Returns the options for radio lists in the page layout settings in the
 * appearance theme settings.
 *
 * @param $theme_name
 */
function page_layouts_device_group_options($theme_name) {
  $device_group_options = drupal_static(__FUNCTION__, array());
  if (empty($device_group_options)) {
    $layout_methods = page_layouts_data_structure();
    foreach ($layout_methods as $method => $values) {
      foreach ($values as $key => $value) {
        if ($key == 'device_groups') {
          $method_values[$method] = $value;
        }
      }
    }
    foreach ($method_values as $this_method => $these_values) {
      foreach ($these_values as $k => $dv) {
        $device_group_options[$dv][] = $this_method;
      }
    }
  }

  return $device_group_options;
}

/**
 * Base config for page layout builder.
 * This is used in mayo_core.submit.responsive.inc to help retrieve the form
 * values for each device groups layout.
 */
function assemble_page_layout() {
  $variables_array = array(
    'layout',
    'media_query',
    'page_width',
    'page_unit',
    'sidebar_first',
    'sidebar_second',
    'sidebar_unit',
  );
  return $variables_array;
}
