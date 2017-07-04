<?php
/**
 * @file
 * gms_text.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function gms_text_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_context|node|text|form';
  $field_group->group_name = 'group_context';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'text';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Context',
    'weight' => '3',
    'children' => array(
      0 => 'field_critical_conversation',
      1 => 'field_intro_manuscript',
      2 => 'field_introduction_to_the_text',
      3 => 'field_keywords',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-context field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_context|node|text|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_files|node|text|form';
  $field_group->group_name = 'group_files';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'text';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Files',
    'weight' => '1',
    'children' => array(
      0 => 'field_image',
      1 => 'field_tei_file',
      2 => 'field_icon',
      3 => 'field_audio',
      4 => 'field_icon_source',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-files field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_files|node|text|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_metadata|node|text|default';
  $field_group->group_name = 'group_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'text';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '7',
    'children' => array(
      0 => 'field_genre',
      1 => 'field_language',
      2 => 'field_period',
      3 => 'field_keywords',
      4 => 'field_year',
      5 => 'field_author',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_metadata|node|text|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_metadata|node|text|form';
  $field_group->group_name = 'group_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'text';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '4',
    'children' => array(
      0 => 'field_genre',
      1 => 'field_language',
      2 => 'field_period',
      3 => 'field_year',
      4 => 'field_author',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-metadata field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_metadata|node|text|form'] = $field_group;

  return $export;
}
