<?php

/**
 * Dashboard form for registered components.
 *
 */
function registry_admin_form($form, &$form_state) {

  $has_disabled = FALSE;
  $components   = registry_get_components();

  foreach($components as $key => $info) {
    $component = new $info['class']();
    $details   = sprintf('%s (%s)', $info['name'], $key);

    if (registry_get_disabled_modules($component)) {
      $has_disabled = TRUE;
      $details .= "*";
    }

    $details .= '<div class="admin-requirements">' . t('Depends on: !modules', [
      '!modules' => implode(', ', _registry_get_decorated_module_list($component->getModuleDependencies())),
    ]) . '</div>';

    $form[$key]['name'] = [
      '#markup' => $details,
    ];
    $form[$key]['url'] = [
      '#markup' => $component->getUrl(),
    ];
    $form[$key]['enabled'][$key] = [
      '#type'    => 'radios',
      '#options' => [
        0 => t('No'),
        1 => t('Yes'),
      ],
      '#default_value' => (int) $component->isEnabled(),
    ];
    $form[$key]['production'] = [
      '#markup' => $component->isProduction() ? t('Yes') : t('No'),
    ];
    $form[$key]['links'] = [
      '#markup' => $component->getConfigUrl() ? l(t('Configure'), $component->getConfigUrl()) : '',
    ];
  }

  if ($has_disabled) {
    $form['disabled'] = [
      '#markup' => '<p>' . t('* One or more modules that this component depends on is disabled or not installed. This component may not be working as expected.') . '</p>',
    ];
  }

  if (!$components) {
    $form['empty'] = [
      '#markup' => '<p>' . t('There are no components currently registered.') . '</p>',
    ];
  }
  else {
    $form['submit'] = [
      '#type'  => 'submit',
      '#value' => t('Update components'),
    ];
  }

  return $form;

}


/**
 * Submission handler for registered component updates.
 *
 */
function registry_admin_form_submit($form, &$form_state) {

  $values   = $form_state['values'];
  $message  = [];
  $enabled  = [];
  $disabled = [];

  foreach(registry_get_components() as $key => $info) {

    $component = new $info['class']();

    if (isset($values[$key]) && $values[$key] != $component->isEnabled()) {
      if ($values[$key]) {
        $action = 'enable';
        $enabled[] = $info['name'];
      }
      else {
        $action = 'disable';
        $disabled[] = $info['name'];
      }

      $component->{$action}();
    }
  }

  if ($enabled) {
    $message[] = t('The following components were enabled: @enabled.', [
      '@enabled' => implode(', ', $enabled),
    ]);
  }

  if ($disabled) {
    $message[] = t('The following components were disabled: @disabled.', [
      '@disabled' => implode(', ', $disabled),
    ]);
  }

  if (!$message) {
    $message[] = t('No changes were selected for any of the components.');
  }

  drupal_set_message(implode(' ', $message));

}


/**
 * Returns a HTML decorated array of modules, depending on if they are enabled
 * or not.
 *
 * @param array $modules
 *   An array of modules to check.
 *
 * @return array
 *
 */
function _registry_get_decorated_module_list(array $modules) {

  return array_map(function($module) {
    $status = module_exists($module) ? 'enabled' : 'disabled';
    return '<span class="admin-' . $status . '">' . $module . '</span>';
  }, $modules);

}