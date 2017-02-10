<?php
global $_theme_name;
$_theme_name = $GLOBALS['theme_key'];

/**
 * @file
 * Provides frequently used functions that load something, ususally CSS or JS
 * files, or that provide assistance to those loaders.
 */

/**
 * Load stylesheet to set the layout.
 *
 * Each time you save the theme settings MAYO builds a layout stylesheet:
 * The file is named: themeName.responsive.layout.css
 *
 * @param $path
 * @param $theme_name
 */
function mayo_load_layout_css($path, $theme_name) {
  global $_theme_name;
  // Get the info file data
  $info = mayo_get_info($theme_name);

  // Load the responsive layout
  $filepath = $path . '/' . $theme_name . '.responsive.layout.css';
  $media_query = 'only screen'; // keyword "only" hide this from unsupporting user agents
  mayo_load_subtheme_responsive_styles($filepath, $media_query, $theme_name, $weight = 0);
}

/**
 * Load Sub-theme Responsive Stylesheets.
 * Wrapper function for drupal_add_css() that takes advantage of Drupals's
 * CSS aggregation logic to trick Drupal into always loading responsive
 * stylesheets in link elements.
 *
 * This is almost always called from mayo_preprocess_html(), only in
 * a rare instance might this be called from a sub-theme (to load additional
 * responsive stylesheets).
 *
 * @param $filepath, path to the CSS file.
 * @param $media_query, the media query from theme settings.
 * @param $theme_name, the active theme.
 * @param $weight, optional.
 */
function mayo_load_subtheme_responsive_styles($filepath, $media_query, $theme_name, $weight = 0) {
  if (file_exists($filepath)) {
    drupal_add_css($filepath, array(
      'preprocess' => variable_get('preprocess_css', '') == 1 ? TRUE : FALSE,
      'group' => CSS_THEME,
      'media' => $media_query,
      'every_page' => TRUE,
      'weight' => $weight,
      )
    );
  }
}
