<?php
/**
 * @file
 * smartdocs_service.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function smartdocs_service_user_default_roles() {
  $roles = array();

  // Exported role: smartdocs service role.
  $roles['smartdocs service role'] = array(
    'name' => 'smartdocs service role',
    'weight' => 11,
  );

  return $roles;
}
