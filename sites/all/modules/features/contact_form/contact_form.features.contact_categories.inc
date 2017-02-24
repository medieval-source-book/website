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
      'recipients' => 'admin@gms.org',
      'reply' => '',
      'weight' => 0,
      'selected' => 1,
    ),
  );
}
