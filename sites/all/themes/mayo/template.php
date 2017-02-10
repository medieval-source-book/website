<?php

/**
 * @file
 * Contains theme override functions and preprocess functions
 */

/**
 * Includes for MAYO css creation form settings.
 */
global $theme_key, $path_to_mayo;
$theme_key = $GLOBALS['theme_key'];
$path_to_mayo = drupal_get_path('theme', 'mayo');
include_once($path_to_mayo . '/inc/load.inc');       // drupal_add_css() wrappers
include_once($path_to_mayo . '/inc/get.inc');        // get theme info, settings, css etc

/**
 * Construct HTML code for the top/bottom block columns
 */
function mayo_build_columns($columns) {
  $styles = array();
  $num_columns = 0;
  $first = -1;

  for ($i = 0 ; $i < 4 ; $i++) {
    if ($columns[$i]) {
      if ($first == -1) $first = $i;
      $last = $i;
      $num_columns++;
    }
  }
  if (!$num_columns) return '';

  $out = '';
  $out .= '<div class="column-blocks clearfix">';

  $column_width = round(100 / $num_columns, 2) . '%';  // calculate percent width of a column

  for ($i = 0 ; $i < 4 ; $i++) {
    if ($columns[$i]) {
      if ($i == $first) {
        $margin_left_style = 'margin-left: 0px;';
      }
      else {
        $margin_left_style = 'margin-left: 5px;';
      }
      if ($i == $last) {
        $margin_right_style = 'margin-right: 0px;';
      }
      else {
        $margin_right_style = 'margin-right: 5px;';
      }
      $style = $margin_left_style . $margin_right_style;

      $out .= '<div class="column-block-wrapper" style="width: ' . $column_width . ';">';
      $out .= '<div class="column-block" style="' . $style . '">';
      $out .= render($columns[$i]);
      $out .= '</div></div> <!--/.column-block --><!--/.column-block-wrapper-->';
    }
  }
  $out .= '</div> <!--/.column-blocks-->';
  $out .= '<div class="spacer clearfix cfie"></div>';
  return $out;
}

/**
 * Implements theme_breadcrumb().
 *
 * Return themed breadcrumb links.
 *
 * @param array $variables
 *   An array containing the breadcrumb links.
 *
 * @return string
 *   A string containing the breadcrumb output.
  */
function mayo_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  // Remove 'Home' and add trailing seperator.
  if (theme_get_setting('homeless_breadcrumb') == 1) {
    if (is_array($breadcrumb)) {
      array_shift($breadcrumb);
    }
    if (!empty($breadcrumb)) {
      $breadcrumb_separator = ' > ';
      $breadcrumb_str = implode($breadcrumb_separator, $breadcrumb);
      $breadcrumb_str .= $breadcrumb_separator;
      $out = '<div class="breadcrumb">' . $breadcrumb_str . '</div>';
      return $out;
    }
  }
  // Bartik style breadcrumb.
  else {
    if (!empty($breadcrumb)) {
      $breadcrumb_separator = ' » ';
      $breadcrumb_str = implode($breadcrumb_separator, $breadcrumb);
      $out = '<div class="breadcrumb">' . $breadcrumb_str . '</div>';
      return $out;
    }
  }
}

/**
 * Custom search block form
 *  Magnifying glass icon used instead of 'submit button'.
 *  Use javascript to show/hide the 'search this site' prompt inside of the text field
 */
function mayo_preprocess_search_block_form(&$variables) {
  $prompt = t('search this site');
  $variables['search'] = array();
  $hidden = array();

  unset($variables['form']['actions']['submit']);
  unset($variables['form']['actions']['#children']);

  $variables['form']['search_block_form']['#value'] = $prompt;
  $variables['form']['search_block_form']['#size'] = theme_get_setting('searchbox_size');
  $variables['form']['search_block_form']['#attributes'] = array(
    'onblur'  => "if (this.value == '') { this.value = '$prompt'; }",
    'onfocus' => "if (this.value == '$prompt') { this.value = ''; }" );

  // we should use 'render' instead of 'drupal_render' since the form is already rendered once.
  foreach (element_children($variables['form']) as $key) {
    $type = $variables['form'][$key]['#type'];
    if ($type == 'hidden' || $type == 'token') {
      $hidden[] = render($variables['form'][$key]);
    }
    else {
      $variables['search'][$key] = render($variables['form'][$key]);
    }
  }
  $variables['search']['hidden'] = implode($hidden);
  $variables['search_form'] = implode($variables['search']);
}

/**
 * Implements hook_process_page().
 */
function mayo_process_page(&$variables) {
  // Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
}

/**
 * Implements hook_preprocess_maintenance_page().
 */
function mayo_preprocess_maintenance_page(&$variables) {
  drupal_add_css(drupal_get_path('theme', 'mayo') . '/css/maintenance-page.css');
}

/**
 * Implements hook_preprocess_html().
 */
function mayo_preprocess_html(&$variables) {
  global $theme_key;
  // Adds classes to <body class="">
  $settings_array = array(
    'round_corners',
    'dark_messages',
  );
  foreach ($settings_array as $setting) {
    if (theme_get_setting($setting) !== 0) {
      $variables['classes_array'][] = theme_get_setting($setting);
    }
  }

  // Add conditional stylesheet for IE
  drupal_add_css(path_to_theme() . '/css/ie8.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'IE 8', '!IE' => FALSE), 'preprocess' => FALSE));
  drupal_add_css(path_to_theme() . '/css/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => ' IE 7', '!IE' => FALSE), 'preprocess' => FALSE));
  drupal_add_css(path_to_theme() . '/css/ie6.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'IE 6', '!IE' => FALSE), 'preprocess' => FALSE));

  $options = array(
    'type' => 'file',
    'group' => CSS_THEME,
    'weight' => 10,
  );

  if (theme_get_setting('menubar_style') == 2) {
    drupal_add_css(drupal_get_path('theme', 'mayo') . '/css/black-menu.css', $options);
  }

  // Add old legacy MAYO styles for Superfish.
  if (theme_get_setting('legacy_superfish_styles') == 1) {
    drupal_add_css(drupal_get_path('theme', 'mayo') . '/css/mayo-superfish.css', $options);
  }

  $options = array(
    'type' => 'inline',
    'group' => CSS_THEME,
    'weight' => 10,
  );

  $font_family = array(
    // Added Japanese font support
    0 => "font-family: Georgia, 'Palatino Linotype', 'Book Antiqua', 'URW Palladio L', Baskerville, Meiryo, 'Hiragino Mincho Pro', 'MS PMincho', serif; ",
    1 => "font-family: Verdana, Geneva, Arial, 'Bitstream Vera Sans', 'DejaVu Sans', Meiryo, 'Hiragino Kaku Gothic Pro', 'MS PGothic', Osaka, sans-serif; ",
  );

  // Add font related stylesheets
  $base_font_size = theme_get_setting('base_font_size');
  $style = 'font-size: ' . $base_font_size . '; ';
  $base_font_family = theme_get_setting('base_font_family');
  if ($base_font_family == 2) { // Custom
    $style .= 'font-family: ' . str_replace(array("&quot;", '\\', '/', '&#039;', '(', ')', ':', ';'), array('"', ''), check_plain(theme_get_setting('base_custom_font_family'))) . ';';
  }
  else {
    $style .= $font_family[$base_font_family];
  }
  drupal_add_css("body {" . $style . "}", $options);

  $heading_font_family = theme_get_setting('heading_font_family');
  if ($heading_font_family == 2) { // Custom
    $style .= 'font-family: ' . str_replace(array("&quot;", '\\', '/', '&#039;', '(', ')', ':', ';'), array('"', ''), check_plain(theme_get_setting('heading_custom_font_family'))) . ';';
  }
  else {
    $style = $font_family[$heading_font_family];
  }
  drupal_add_css("h1,h2,h3,h4,h5 {" . $style . "}", $options);

  if ($heading_font_family == 1) {
    // in case of san-serif fonts, make heading font sizes slightly smaller
    drupal_add_css(".sidebar h2 { font-size: 1.2em; }", $options);
    drupal_add_css("#content .node h2 { font-size: 1.4em; }", $options);
  }
    // Get the path to the directory where our CSS files are saved
  $theme_name = $theme_key;
  $path = variable_get('theme_' . $theme_name . '_files_directory');
    // Load Layout
  mayo_load_layout_css($path, $theme_name);
}

/**
 * Implements hook_process_html().
 */
function mayo_process_html(&$variables) {
  // Hook into color.module
  if (module_exists('color')) {
    _color_html_alter($variables);
  }
}

/**
 * Implements hook_page_alter().
 */
function mayo_page_alter($page) {
  // Add meta tag for viewport, for easier responsive theme design.
  $viewport = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1',
    ),
  );
  drupal_add_html_head($viewport, "viewport");
}