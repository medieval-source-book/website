<?php
/**
 * @file
 * Theme preprocessors.
 */

/**
 * Prepares variables for the TimelineJS style template.
 */
function template_preprocess_views_timelinejs(&$vars) {
  $library_location = variable_get('views_timelinejs_library', 'cdn');
  $view = $vars['view'];

  $id = drupal_html_id('timelinejs_' . $view->name . '_' . $view->current_display);
  $style = 'width: ' . $vars['timeline_options']['width'] . '; height: ' .  $vars['timeline_options']['height'] . ';';
  $vars['div_attributes'] = drupal_attributes(array('id' => $id, 'style' => $style, 'class' => 'timelinejs'));

  // Load required libraries and styles.
  $library = drupal_add_library('views_timelinejs', 'timelinejs.' . $library_location);

  // Add inline JavaScript.
  $settings = array(
    'options' => _sanitize_timeline_options($vars['timeline_options']),
    'source' => $vars['rows'],
    'embed_id' => $id,
    'processed' => FALSE,
  );
  drupal_add_js(array('timelineJS' => array($settings)), 'setting');
  drupal_add_js(drupal_get_path('module', 'views_timelinejs') . '/js/views_timelinejs.js');

  // Add alternate font CSS.
  if ($vars['timeline_font']) {
    $font_library = drupal_add_library('views_timelinejs', 'timelinejs.' . $vars['timeline_font'] . '.' . $library_location);
  }
}

/**
 * Sanitizes the timeline options.
 */
function _sanitize_timeline_options($options) {
  // Sanitize the options.
  $options = array_map('check_plain', $options);
  // Remove empty values from the options before returning.
  return array_filter($options);
}
