<?php
/**
 * @file
 * submissions.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function submissions_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function submissions_node_info() {
  $items = array(
    'submission' => array(
      'name' => t('Submission'),
      'base' => 'node_content',
      'description' => t('For users to submit transcriptions and translations.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
