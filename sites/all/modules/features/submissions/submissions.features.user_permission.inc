<?php
/**
 * @file
 * submissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function submissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create submission content'.
  $permissions['create submission content'] = array(
    'name' => 'create submission content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any submission content'.
  $permissions['delete any submission content'] = array(
    'name' => 'delete any submission content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own submission content'.
  $permissions['delete own submission content'] = array(
    'name' => 'delete own submission content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any submission content'.
  $permissions['edit any submission content'] = array(
    'name' => 'edit any submission content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own submission content'.
  $permissions['edit own submission content'] = array(
    'name' => 'edit own submission content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
