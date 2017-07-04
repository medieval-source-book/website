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
        0 => 'field_icon',
        1 => 'field_vm_link',
        2 => 'group_metadata',
        3 => 'field_icon_source',
        6 => 'field_author',
        7 => 'field_year',
        9 => 'field_language',
        10 => 'field_period',
        11 => 'field_genre',
        12 => 'field_keywords',
      ),
      'right' => array(
        4 => 'field_display_title',
        5 => 'field_introduction_to_the_text',
        8 => 'field_critical_conversation',
      ),
    ),
    'fields' => array(
      'field_icon' => 'left',
      'field_vm_link' => 'left',
      'group_metadata' => 'left',
      'field_icon_source' => 'left',
      'field_display_title' => 'right',
      'field_introduction_to_the_text' => 'right',
      'field_author' => 'left',
      'field_year' => 'left',
      'field_critical_conversation' => 'right',
      'field_language' => 'left',
      'field_period' => 'left',
      'field_genre' => 'left',
      'field_keywords' => 'left',
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
