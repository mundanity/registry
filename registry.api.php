<?php

/**
 * Define components that will be managed by the registry.
 *
 * Components are structured in a similar fashion to Drupal menu items, and have
 * the following configuration options:
 * - class: (required) The class that will handle this component. This class
 *   must implement the "ComponentInterface" interface.
 * - name: (required) The human readable name of the component.
 *
 * The key for each element in the array should be a machine name to describe
 * the component.
 *
 * @return array
 *
 */
function hook_registry_info() {

  $items['componen1'] = [
    'class' => 'Drupal\mymodule\MyService',
    'name'  => 'My service',
  ];
  $items['other_resource'] = [
    'class' => 'Drupal\my_other_module\OtherResource',
    'name'  => 'Other resource',
  ];

  return $items;

}