<?php
/**
 * @file
 * contact_form.features.contact_categories.inc
 */

/**
 * Implements hook_contact_categories_defaults().
 */
function contact_form_contact_categories_defaults() {
  return array(
    'Website feedback' => array(
      'category' => 'Website feedback',
      'recipients' => 'starkey@stanford.edu,maelp@stanford.edu,mikewidner@stanford.edu',
      'reply' => '',
      'weight' => 0,
      'selected' => 1,
    ),
  );
}
