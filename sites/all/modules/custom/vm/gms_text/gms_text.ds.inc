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
    'field_genre' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_minimal',
          'lb' => 'Genre | ',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_language' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_minimal',
          'lb' => 'Language | ',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_period' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_minimal',
          'lb' => 'Period | ',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_tei_file' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
    'field_vm_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
        ),
      ),
    ),
    'field_keywords' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_minimal',
          'lb' => 'Keywords | ',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_author' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_minimal',
          'lb' => 'Author | ',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_icon_source' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_field',
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
      'format' => 'full_html',
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
        4 => 'field_icon_source',
        9 => 'field_author',
        10 => 'field_language',
        11 => 'field_period',
        12 => 'field_genre',
        13 => 'field_keywords',
        14 => 'field_tei_file',
      ),
      'right' => array(
        5 => 'field_introduction_to_the_text',
        6 => 'field_intro_manuscript',
        7 => 'field_critical_conversation',
        8 => 'field_about_edition',
      ),
    ),
    'fields' => array(
      'text_title' => 'header',
      'field_icon' => 'left',
      'field_vm_link' => 'left',
      'group_metadata' => 'left',
      'field_icon_source' => 'left',
      'field_introduction_to_the_text' => 'right',
      'field_intro_manuscript' => 'right',
      'field_critical_conversation' => 'right',
      'field_about_edition' => 'right',
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
