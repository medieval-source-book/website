<?php
/**
 * @file
 * gms_text.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function gms_text_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|text|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'text';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'text_title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'lb-col' => TRUE,
        ),
      ),
    ),
  );
  $export['node|text|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function gms_text_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'text_title';
  $ds_field->label = 'Text Title[node:field_original_language_title]';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '[node:title] | [node:field_original_language_title]',
      'format' => 'plain_text',
    ),
    'use_token' => 1,
  );
  $export['text_title'] = $ds_field;

  return $export;
}

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
        0 => 'text_title',
      ),
      'left' => array(
        1 => 'field_icon',
        2 => 'field_vm_link',
        3 => 'group_metadata',
        4 => 'field_author',
        5 => 'field_icon_source',
        6 => 'field_language',
        7 => 'field_tei_file',
        8 => 'field_period',
        10 => 'field_genre',
        13 => 'field_keywords',
      ),
      'right' => array(
        9 => 'field_introduction_to_the_text',
        11 => 'field_intro_manuscript',
        12 => 'field_critical_conversation',
      ),
    ),
    'fields' => array(
      'text_title' => 'header',
      'field_icon' => 'left',
      'field_vm_link' => 'left',
      'group_metadata' => 'left',
      'field_author' => 'left',
      'field_icon_source' => 'left',
      'field_language' => 'left',
      'field_tei_file' => 'left',
      'field_period' => 'left',
      'field_introduction_to_the_text' => 'right',
      'field_genre' => 'left',
      'field_intro_manuscript' => 'right',
      'field_critical_conversation' => 'right',
      'field_keywords' => 'left',
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
