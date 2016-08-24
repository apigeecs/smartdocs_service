<?php
/**
 * @file
 * smartdocs_service.services.inc
 */

/**
 * Implements hook_default_services_endpoint().
 */
function smartdocs_service_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass();
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'smartdocs_service';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'smartdocs/apis';
  $endpoint->authentication = array(
    'services_basic_auth' => 'services_basic_auth',
  );
  $endpoint->server_settings = array(
    'formatters' => array(
      'json' => TRUE,
      'bencode' => FALSE,
      'jsonp' => FALSE,
      'php' => FALSE,
      'xml' => FALSE,
      'yaml' => FALSE,
    ),
    'parsers' => array(
      'application/json' => TRUE,
      'application/x-www-form-urlencoded' => TRUE,
      'application/x-yaml' => TRUE,
      'multipart/form-data' => TRUE,
      'application/vnd.php.serialized' => FALSE,
      'application/xml' => FALSE,
      'text/xml' => FALSE,
    ),
  );
  $endpoint->resources = array(
    'smartdocs' => array(
      'alias' => 'models',
      'operations' => array(
        'retrieve' => array(
          'enabled' => '1',
        ),
        'create' => array(
          'enabled' => '1',
        ),
        'update' => array(
          'enabled' => '1',
        ),
        'delete' => array(
          'enabled' => '1',
        ),
        'index' => array(
          'enabled' => '1',
        ),
      ),
      'actions' => array(
        'queue_status' => array(
          'enabled' => '1',
        ),
      ),
      'targeted_actions' => array(
        'render' => array(
          'enabled' => '1',
        ),
        'import' => array(
          'enabled' => '1',
        ),
      ),
    ),
  );
  $endpoint->debug = 0;
  $export['smartdocs_service'] = $endpoint;

  return $export;
}
