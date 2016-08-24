<?php
/**
 * @file
 * smartdocs_service.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function smartdocs_service_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access smartdocs operations using apis'.
  $permissions['access smartdocs operations using apis'] = array(
    'name' => 'access smartdocs operations using apis',
    'roles' => array(
      'administrator' => 'administrator',
      'smartdocs service role' => 'smartdocs service role',
    ),
    'module' => 'smartdocs_service',
  );

  return $permissions;
}
