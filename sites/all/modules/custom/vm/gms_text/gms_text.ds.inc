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
  $ds_layout->layout = 'ds_2col_stacked_fluid';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_icon',
        1 => 'field_vm_link',
        2 => 'field_icon_source',
        3 => 'field_display_title',
        4 => 'field_author',
        5 => 'field_introduction_to_the_text',
        6 => 'field_critical_conversation',
        7 => 'field_year',
        8 => 'field_language',
        9 => 'field_period',
        10 => 'field_genre',
        11 => 'field_keywords',
        12 => 'field_original_language_title',
      ),
    ),
    'fields' => array(
      'field_icon' => 'header',
      'field_vm_link' => 'header',
      'field_icon_source' => 'header',
      'field_display_title' => 'header',
      'field_author' => 'header',
      'field_introduction_to_the_text' => 'header',
      'field_critical_conversation' => 'header',
      'field_year' => 'header',
      'field_language' => 'header',
      'field_period' => 'header',
      'field_genre' => 'header',
      'field_keywords' => 'header',
      'field_original_language_title' => 'header',
    ),
    'classes' => array(),
    'wrappers' => array(),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => TRUE,
    'layout_link_attribute' => FALSE,
    'layout_link_custom' => '',
    'layout_disable_css' => 0,
  );
  $export['node|text|default'] = $ds_layout;

  return $export;
}
