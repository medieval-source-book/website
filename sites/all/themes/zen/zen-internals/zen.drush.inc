<?php
/**
 * @file
 * Contains functions only needed for drush integration.
 */

/**
 * Implementation of hook_drush_command().
 */
function zen_drush_command() {
  $items = array();

  $items['zen'] = array(
    'description' => 'Create a theme using Zen.',
    'arguments' => array(
      'machine_name' => '[optional] A machine-readable name for your theme.',
      'name'         => 'A name for your theme.',
    ),
    'options' => array(
      'name'         => 'A name for your theme.',
      'machine-name' => '[a-z, 0-9, _] A machine-readable name for your theme.',
      'path'         => 'The path where your theme will be created. Defaults to: sites/all/themes',
      'description'  => 'A description of your theme.',
    ),
    'examples' => array(
      'drush zen "Amazing name"' => 'Create a sub-theme, using the default options.',
      'drush zen zomg_amazing "Amazing name"' => 'Create a sub-theme with a specific machine name.',
      'drush zen "Amazing name" --path=sites/default/themes --description="So amazing."' => 'Create a sub-theme in the specified directory with a custom description.',
    ),
  );

  return $items;
}

/**
 * Create a Zen sub-theme using the starter kit.
 */
function drush_zen($machine_name = NULL, $name = NULL) {
  // Determine the theme name and machine name.
  if (!isset($name)) {
    // If only given one argument, it is the $name.
    if (isset($machine_name)) {
      $name = $machine_name;
      unset($machine_name);
    }
    else {
      $name = drush_get_option('name');
    }

    if (!isset($machine_name)) {
      $machine_name = drush_get_option('machine-name');
    }
  }

  if (!$name) {
    if ($machine_name) {
      $name = $machine_name;
    }
    else {
      if (FALSE) {
        // Allow localize.drupal.org to pick up the string to translate.
        t('The name of the theme was not specified.');
      }
      return drush_set_error('ZEN_SUBTHEME_NAME_NOT_SPECIFIED', dt('The name of the theme was not specified.'));
    }
  }

  if (!$machine_name) {
    $machine_name = $name;
  }

  // Clean up the machine name.
  $machine_name = str_replace(' ', '_', strtolower($machine_name));
  $search = array(
    '/[^a-z0-9_]/', // Remove characters not valid in function names.
    '/^[^a-z]+/',   // Functions must begin with an alpha character.
  );
  $machine_name = preg_replace($search, '', $machine_name);

  // Determine the path to the new sub-theme.
  $subtheme_path = 'sites/all/themes';
  if ($path = drush_get_option('path')) {
    $subtheme_path = drush_trim_path($path);
  }
  $subtheme_path = drush_normalize_path(drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . $subtheme_path . '/' . $machine_name);

  // Ensure the destination directory exists.
  if (!is_dir(dirname($subtheme_path))) {
    if (FALSE) {
      // Allow localize.drupal.org to pick up the string to translate.
      t('The directory "!directory" was not found.', array('!directory' => dirname($subtheme_path)));
    }
    return drush_set_error('ZEN_DESTINATION_NOT_FOUND', dt('The directory "!directory" was not found.', array('!directory' => dirname($subtheme_path))));
  }

  // Ensure the STARTERKIT directory exists.
  $starterkit_path = drush_normalize_path(drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . drupal_get_path('theme', 'zen') . '/STARTERKIT');
  if (!is_dir($starterkit_path)) {
    if (FALSE) {
      // Allow localize.drupal.org to pick up the string to translate.
      t('The STARTERKIT directory was not found in "!directory"', array('!directory' => dirname($starterkit_path)));
    }
    return drush_set_error('ZEN_STARTERKIT_NOT_FOUND', dt('The STARTERKIT directory was not found in "!directory"', array('!directory' => dirname($starterkit_path))));
  }

  // Make a fresh copy of the original starter kit.
  drush_op('drush_copy_dir', $starterkit_path, $subtheme_path);

  // Rename the .info file.
  $subtheme_info_file = $subtheme_path . '/' . $machine_name . '.info';
  drush_op('rename', drush_normalize_path($subtheme_path . '/STARTERKIT.info.txt'), drush_normalize_path($subtheme_info_file));

  // Alter the contents of the .info file based on the command options.
  $alterations = array(
    '= Zen Sub-theme Starter Kit' => '= ' . $name,
  );
  if ($description = drush_get_option('description')) {
    $alterations['Read the <a href="https://drupal.org/node/873778">online docs</a> or the included README.txt on how to create a theme with Zen.'] = $description;
  }
  drush_op('zen_file_str_replace', $subtheme_info_file, array_keys($alterations), $alterations);

  // Replace all occurrences of 'STARTERKIT' with the machine name of our sub theme.
  drush_op('zen_file_str_replace', $subtheme_path . '/theme-settings.php', 'STARTERKIT', $machine_name);
  drush_op('zen_file_str_replace', $subtheme_path . '/template.php', 'STARTERKIT', $machine_name);

  // Notify user of the newly created theme.
  if (FALSE) {
    // Allow localize.drupal.org to pick up the string to translate.
    t('Starter kit for "!name" created in: !path', array('!name' => $name, '!path' => $subtheme_path));
  }
  drush_print(dt('Starter kit for "!name" created in: !path', array(
    '!name' => $name,
    '!path' => $subtheme_path,
  )));
}

/**
 * Replace strings in a file.
 */
function zen_file_str_replace($file_path, $find, $replace) {
  $file_path = drush_normalize_path($file_path);
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  file_put_contents($file_path, $file_contents);
}
