<?php
/**
 * @file
 * gms_text.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function gms_text_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|text|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'text';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_vm_link',
        1 => 'field_introduction_to_the_text',
        2 => 'field_intro_manuscript',
        3 => 'field_critical_conversation',
      ),
      'right' => array(
        4 => 'field_language',
        5 => 'field_genre',
        6 => 'field_period',
        7 => 'field_keywords',
        8 => 'field_image',
      ),
    ),
    'fields' => array(
      'field_vm_link' => 'left',
      'field_introduction_to_the_text' => 'left',
      'field_intro_manuscript' => 'left',
      'field_critical_conversation' => 'left',
      'field_language' => 'right',
      'field_genre' => 'right',
      'field_period' => 'right',
      'field_keywords' => 'right',
      'field_image' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left' => 'div',
      'right' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => 0,
  );
  $export['node|text|default'] = $ds_layout;

  return $export;
}
