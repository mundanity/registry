<?php

/**
 * Implements hook_drush_command().
 *
 * Callbacks are explicitly defined in order to avoid namespace collision with
 * some versions of Drush that have a "drush_registry_rebuild()" function.
 *
 */
function registry_drush_command() {

  $items['registry-list'] = [
    'description' => dt('Returns a list of available components'),
    'callback'    => 'registry_drush_list',
  ];
  $items['registry-rebuild'] = [
    'description' => dt('Rebuild the component cache, reporting any errors found within component definitions.'),
    'callback'    => 'registry_drush_rebuild',
  ];
  $items['registry-enable'] = [
    'description' => dt('Enable the specified component'),
    'arguments'   => ['component' => NULL],
    'callback'    => 'registry_drush_enable',
  ];
  $items['registry-disable'] = [
    'description' => dt('Disable the specified component'),
    'arguments'   => ['component' => NULL],
    'callback'    => 'registry_drush_disable',
  ];

  return $items;

}


/**
 * Returns a list of available components.
 *
 */
function registry_drush_list() {

  $components = registry_get_components();
  $rows = [
    [dt('Component'), dt('URL'), dt('Enabled')],
  ];

  foreach($components as $key => $info) {
    $component = new $info['class']();
    $rows[]    = [
      sprintf('%s (%s)', $info['name'], $key),
      $component->getUrl(),
      $component->isEnabled() ? dt('Yes') : dt('No'),
    ];
  }

  drush_print_table($rows, TRUE);
  drush_log(dt('Displaying !count registered components', [
    '!count' => count($components),
  ]), 'ok');

}


/**
 * Re-caches the components, which will generate warnings or errors for
 * problematic definitions.
 *
 */
function registry_drush_rebuild() {

  $components = registry_get_components(TRUE);

  drush_log(dt('!count components have been verified and cached', [
    '!count' => count($components),
  ]), 'ok');

}


/**
 * Enables the specified component.
 *
 * @param string $name
 *  The machine name of the component to enable.
 *
 */
function registry_drush_enable($name) {

  $components = registry_get_components();

  if (!$name) {
    return;
  }

  if (!isset($components[$name])) {
    drush_log(dt('The component "@component" does not exist! Use "drush registry-list" to list registered components.', [
      '@component' => $name,
    ]), 'error');
    return;
  }

  $info = $components[$name];
  $component = new $info['class']();

  if ($component->isEnabled()) {
    drush_log(dt('The component "@component" is already enabled.', [
      '@component' => $name,
    ]), 'error');
    return;
  }

  $component->enable();
  drush_log(dt('The component "@component" has been enabled.', [
    '@component' => $name,
  ]), 'ok');

}


/**
 * Disables the specified component.
 *
 * @param string $name
 *  The machine name of the component to disable.
 *
 */
function registry_drush_disable($name) {

  $components = registry_get_components();

  if (!$name) {
    return;
  }

  if (!isset($components[$name])) {
    drush_log(dt('The component "@component" does not exist! Use "drush registry-list" to list registered components.', [
      '@component' => $name,
    ]), 'error');
    return;
  }

  $info = $components[$name];
  $component = new $info['class']();

  if (!$component->isEnabled()) {
    drush_log(dt('The component "@component" is already disabled.', [
      '@component' => $name,
    ]), 'error');
    return;
  }

  $component->disable();
  drush_log(dt('The component "@component" has been disabled.', [
    '@component' => $name,
  ]), 'ok');

}