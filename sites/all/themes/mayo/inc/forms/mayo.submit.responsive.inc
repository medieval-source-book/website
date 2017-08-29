<?php

/**
 * @file
 * Build and save the responsive layout.
 *
 * This is the main submit handler for building the layout.
 * The output is a stylesheet saved to public
 * files - the main responsive layout.
 */
function mayo_submit_reponsive($values, $theme_name, $path) {
  global $_path_to_mayo;
  // Set up some paths we use to get and save files
  $path_to_responsive_css = drupal_get_path('theme', $theme_name) . '/css/';
  $path_to_panels_css = $_path_to_mayo . '/layouts/css/';

  // Get the page layout config array
  $layout_variables = assemble_page_layout();

  // $layouts will hold all the page level layouts
  $layouts = array();

  // Initialize the $is_default_layout variable, we use this to test against
  $is_default_layout = 'smalltouch-portrait';

  // Holds all styles from the responsive stylesheets
  $responsive_styles = array();

  // Smalltouch Landscape
  if ($values['smalltouch_landscape_layout']) {

    $device = 'smalltouch_landscape';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $smalltouch_landscape_layout_data[$value] = check_plain($values["$device" . '_' . "$value"]);
      }
    }
    $layout = mayo_build_page_layout($smalltouch_landscape_layout_data['layout'], $smalltouch_landscape_layout_data['sidebar_first'], $smalltouch_landscape_layout_data['sidebar_second'], $smalltouch_landscape_layout_data['sidebar_unit'], $theme_name);

    $method = $smalltouch_landscape_layout_data['layout'];
    $comment = "/* $device $method */\n";
    $width = "\n" . '#page-wrapper {width:' . $smalltouch_landscape_layout_data['page_width'] . $smalltouch_landscape_layout_data['page_unit'] . '}';
    $media_query = $smalltouch_landscape_layout_data['media_query'];

    // Build the styles string
    $styles = $width . "\n" . $layout;

    // CSS wrapped in the media query
    $css = $comment . '@media ' . $media_query . ' {' . $styles . "\n" . '}';

    // Get and wrap the responsive CSS styles in the relative media query
    $responsive_smalltouch_landscape_css = '';
    $layouts[] = $css;
  }

  // Tablet Portrait
  if ($values['tablet_portrait_layout']) {

    $device = 'tablet_portrait';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $tablet_portrait_layout_data[$value] = check_plain($values["$device" . '_' . "$value"]);
      }
    }
    // Workaround upgrade issues for some settings
    if ($tablet_portrait_layout_data['layout'] == 'two_col_stack') {
      $tablet_portrait_layout_data['layout'] = 'two_sidebars_right_stack';
    }
    $layout = mayo_build_page_layout($tablet_portrait_layout_data['layout'], $tablet_portrait_layout_data['sidebar_first'], $tablet_portrait_layout_data['sidebar_second'], $tablet_portrait_layout_data['sidebar_unit'], $theme_name);

    $method = $tablet_portrait_layout_data['layout'];
    $comment = "/* $device $method */\n";
    $width = "\n" . '#page-wrapper {width:' . $tablet_portrait_layout_data['page_width'] . $tablet_portrait_layout_data['page_unit'] . '}';
    $media_query = $tablet_portrait_layout_data['media_query'];

    // Build the styles string
    $styles = $width . "\n" . $layout;

    // CSS wrapped in the media query
    $css = $comment . '@media ' . $media_query . ' {' . $styles . "\n" . '}';
    $layouts[] = $css;
  }

  // Tablet Landscape
  if ($values['tablet_landscape_layout']) {

    $device = 'tablet_landscape';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $tablet_landscape_layout_data[$value] = check_plain($values["$device" . '_' . "$value"]);
      }
    }
    // Workaround upgrade issues for some settings
    if ($tablet_portrait_layout_data['layout'] == 'two_col_stack') {
      $tablet_portrait_layout_data['layout'] = 'two_sidebars_right_stack';
    }
    $layout = mayo_build_page_layout($tablet_landscape_layout_data['layout'], $tablet_landscape_layout_data['sidebar_first'], $tablet_landscape_layout_data['sidebar_second'], $tablet_landscape_layout_data['sidebar_unit'], $theme_name);

    $method = $tablet_landscape_layout_data['layout'];
    $comment = "/* $device $method */\n";
    $width = "\n" . '#page-wrapper {width:' . $tablet_landscape_layout_data['page_width'] . $tablet_landscape_layout_data['page_unit'] . '}';
    $media_query = $tablet_landscape_layout_data['media_query'];

    // Build the styles string
    $styles = $width . "\n" . $layout;

    // CSS wrapped in the media query
    $css = $comment . '@media ' . $media_query . ' {' . $styles . "\n" . '}';
    $layouts[] = $css;
  }
  // Standard Layout (bigscreen)
  if ($values['bigscreen_layout']) {

    $device = 'bigscreen';
    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $bigscreen_layout_data[$value] = check_plain($values["$device" . '_' . "$value"]);
      }
    }
    $layout = mayo_build_page_layout($bigscreen_layout_data['layout'], $bigscreen_layout_data['sidebar_first'], $bigscreen_layout_data['sidebar_second'], $bigscreen_layout_data['sidebar_unit'], $theme_name);

    $method = $bigscreen_layout_data['layout'];
    $comment = "/* $device $method */";
    $width = "\n" . '#page-wrapper {width:' . $bigscreen_layout_data['page_width'] . $bigscreen_layout_data['page_unit'] . '}';
    $media_query = $bigscreen_layout_data['media_query'];

    // Standard layout can have a max-width
    $values['bigscreen_set_max_width'] = 0;
    if ($values['bigscreen_set_max_width'] === 1 && $bigscreen_layout_data['page_unit'] === '%') {
      if (!empty($values['bigscreen_max_width'])) {
        $width = "\n" . '#page-wrapper {width:' . $bigscreen_layout_data['page_width'] . $bigscreen_layout_data['page_unit'] . ';max-width:' . $values['bigscreen_max_width'] . $values['bigscreen_max_width_unit'] . '}';
      }
      else {
        $width = "\n" . '#page-wrapper {width:' . $bigscreen_layout_data['page_width'] . $bigscreen_layout_data['page_unit'] . ';max-width:' . $values['bigscreen_max_width'] . $values['bigscreen_max_width_unit'] . '}';
      }
    }

    // Build the styles string
    $styles = $width . "\n" . $layout;
    $css = $comment . "\n" . '@media ' . $media_query . ' {' . $styles . "\n" . '}';

    // add $css to the layouts array
    $layouts[] = $css;
  }
  //****** END bigscreen layout ******//

  // Get and wrap the responsive CSS styles in the relative media query
  // responsive layout
  $responsive_layout_data = implode("\n", $layouts);
  $responsive_layout = $responsive_layout_data;

  // Aggregate the design stylesheets
  $responsive_css = implode("\n", $responsive_styles);

  // Regex relative paths. This mimics Drupal core drupal_build_css_cache(), but
  // its not as powerful because assets must be relative to the theme root.
  $_base = base_path() . $path_to_responsive_css;
  _drupal_build_css_path(NULL, $_base);
  $responsive_css = preg_replace_callback('/url\(\s*[\'"]?(?![a-z]+:|\/+)([^\'")]+)[\'"]?\s*\)/i', '_drupal_build_css_path', $responsive_css);

  // Build a keyed array: file names as key, layout data as value
  $files = array(
    "$theme_name.responsive.layout" => $responsive_layout,
  );

  // Loop over the array and save each file, and we're done!
  foreach ($files as $key => $value) {
    $filepath = "$path/$key.css";
    file_unmanaged_save_data($value, $filepath, FILE_EXISTS_REPLACE);
  }
}
