<?php

use Apigee\ManagementAPI\APIProxy;
use Apigee\SmartDocs\Model;
use Apigee\SmartDocs\Revision;
require_once drupal_get_path('module', 'smartdocs') . "/smartdocs.admin.inc";
require_once drupal_get_path('module', 'smartdocs') . "/batch/smartdocs.render.inc";

/**
 * SmartDocs Import Callback
 *
 * @param $model_name
 * @param $fields
 * @return mixed|string
 */
function _smartdocs_service_swagger_import( $model_name, $fields ) {
  $formats =  array('yaml' => 'swagger', 'json' => 'swagger', 'xml' =>'wadl');
  $tmp = explode(".", $_FILES['api_definition']['name']);
  $ext = array_pop($tmp);
  if(!isset($formats[$ext])) {
    return services_error(t('unknown format'), 500);
  }
  $model = new Model(devconnect_default_org_config());
  $model->load($model_name);
  $model->importFile(file_get_contents($_FILES['api_definition']['tmp_name']), $formats[$ext], "application/" . $ext);
  return "Import Successful";
}

/**
 * SmartDocs Render Callback
 * @param $name
 * @return string
 */
function _smartdocs_service_swagger_render( $name ) {
  drupal_set_time_limit(0);
  $config = devconnect_default_org_config();
  $model = new Model($config);
  $model->load($name);
  $revision = new Revision($config, $model->getUuid());
  $revision->load($model->getLatestRevisionNumber());
  $selected = array();
  foreach($revision->getResources() as $resource){
    foreach($resource->getMethods() as $method) {
      $selected[$method->getUuid()] = $method->getUuid();
    }
  }
  $batch = smartdocs_render($model, $revision, $selected, array('publish' => TRUE));
  $queue = DrupalQueue::get('smartdocs_service_queue');
  foreach($batch['operations'] as $op){
    $queue->createItem($op);
  }
  return 'Items have been added to the queue for rendering';
}

/**
 * Retrieve a SmartDocs model
 *
 * @param $model_name
 * @return array
 */
function _smartdocs_model_resource_retrieve($model_name) {
  $model = new Model(devconnect_default_org_config());
  $model->load($model_name);
  return $model->toArray();
}

/**
 * Create a SmartDocs model
 *
 * @param $model_name
 * @param $display_name
 * @param $model_description
 * @return string
 */
function _smartdocs_model_resource_create($model_name, $display_name,  $model_description){
  if (empty($display_name)) {
    $display_name = $model_name;
  }

  $form_state = array();
  $form_state['values']['model_name'] = $model_name;
  $form_state['values']['display_name'] = $display_name;
  $form_state['values']['model_description'] = $model_description;
  smartdocs_add_model_submit(array(), $form_state);
  return "Model added";
}

/**
 * Update a SmartDocs model
 *
 *
 * @param $model_name
 * @param $display_name
 * @param $model_description
 * @return string
 */
function _smartdocs_model_resource_update($model_name, $display_name,  $model_description){
  $model = new Model(devconnect_default_org_config());
  $model->load($model_name);
  if (empty($display_name)) {
    $model->setDisplayName($display_name);
  }
  $model->setDescription($model_description);
  $model->save(TRUE);
  return "Model updated";
}

/**
 * Delete a Smartdocs model
 *
 * @param $model_name
 * @return string
 */
function _smartdocs_model_resource_delete($model_name){
  $model = new Model(devconnect_default_org_config());
  $model->load($model_name);
  $form_state = array();
  $form_state['values']['model'] = $model->toArray();
  smartdocs_model_delete_submit(array(), $form_state);
  return "Delete successful";
}

/**
 * List all the SmartDocs Model
 *
 * @return array
 */
function _smartdocs_model_resource_index(){
  $model = new Model(devconnect_default_org_config());
  $return = array();
  foreach($model->listModels() as $model){
    $return[$model->getName()] = $model->toArray();
  }
  return $return;
}

/**
 * Count of the pending items in smartdocs_service_queue
 */
function _smartdocs_service_queue_status(){
  $queue = DrupalQueue::get('smartdocs_service_queue');
  return array('pending_items' => $queue->numberOfItems());
}