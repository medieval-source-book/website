<?php
/**
 * @file
 * gms_text.features.inc
 */

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
