<?php
/**
 * @file
 * gms_text.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function gms_text_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create text content'.
  $permissions['create text content'] = array(
    'name' => 'create text content',
    'roles' => array(
      'Team Member' => 'Team Member',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any text content'.
  $permissions['delete any text content'] = array(
    'name' => 'delete any text content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own text content'.
  $permissions['delete own text content'] = array(
    'name' => 'delete own text content',
    'roles' => array(
      'Team Member' => 'Team Member',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any text content'.
  $permissions['edit any text content'] = array(
    'name' => 'edit any text content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own text content'.
  $permissions['edit own text content'] = array(
    'name' => 'edit own text content',
    'roles' => array(
      'Team Member' => 'Team Member',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
