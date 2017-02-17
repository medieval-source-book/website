<?php
/**
 * @file
 * gms_text.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gms_text_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function gms_text_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function gms_text_image_default_styles() {
  $styles = array();

  // Exported image style: cropped_rectangle.
  $styles['cropped_rectangle'] = array(
    'label' => 'Cropped rectangle',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 300,
          'height' => 200,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function gms_text_node_info() {
  $items = array(
    'text' => array(
      'name' => t('Text'),
      'base' => 'node_content',
      'description' => t('For describing texts in the sourcebook'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
