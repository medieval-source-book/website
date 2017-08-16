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
    'combined_title_field' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
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
  $ds_field->field = 'combined_title_field';
  $ds_field->label = 'Combined title field';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'text|*';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<h2><span class="eng-node-title">[node:title]</span> | <span class="original-node-title"><em>[node:field_original_language_title]</em></h2></span>',
      'format' => 'full_html',
    ),
    'use_token' => 1,
  );
  $export['combined_title_field'] = $ds_field;

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
      'left' => array(
        0 => 'field_icon',
        1 => 'field_vm_link',
        2 => 'group_metadata',
        3 => 'field_icon_source',
        7 => 'field_author',
        8 => 'field_language',
        9 => 'field_period',
        10 => 'field_genre',
        11 => 'field_keywords',
      ),
      'right' => array(
        4 => 'combined_title_field',
        5 => 'field_introduction_to_the_text',
        6 => 'field_critical_conversation',
      ),
    ),
    'fields' => array(
      'field_icon' => 'left',
      'field_vm_link' => 'left',
      'group_metadata' => 'left',
      'field_icon_source' => 'left',
      'combined_title_field' => 'right',
      'field_introduction_to_the_text' => 'right',
      'field_critical_conversation' => 'right',
      'field_author' => 'left',
      'field_language' => 'left',
      'field_period' => 'left',
      'field_genre' => 'left',
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
