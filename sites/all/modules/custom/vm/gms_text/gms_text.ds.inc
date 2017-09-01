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
      'left' => array(
        0 => 'field_icon',
        1 => 'field_icon_source',
        2 => 'field_vm_link',
        3 => 'group_metadata',
        8 => 'field_author',
        9 => 'field_language',
        10 => 'field_period',
        11 => 'field_genre',
        12 => 'field_keywords',
        13 => 'field_tei_file',
      ),
      'right' => array(
        4 => 'field_introduction_to_the_text',
        5 => 'field_intro_manuscript',
        6 => 'field_about_edition',
        7 => 'field_critical_conversation',
      ),
    ),
    'fields' => array(
      'field_icon' => 'left',
      'field_icon_source' => 'left',
      'field_vm_link' => 'left',
      'group_metadata' => 'left',
      'field_introduction_to_the_text' => 'right',
      'field_intro_manuscript' => 'right',
      'field_about_edition' => 'right',
      'field_critical_conversation' => 'right',
      'field_author' => 'left',
      'field_language' => 'left',
      'field_period' => 'left',
      'field_genre' => 'left',
      'field_keywords' => 'left',
      'field_tei_file' => 'left',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
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
