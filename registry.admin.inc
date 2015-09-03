<?php

use Drupal\registry\ConfigurableComponentInterface;
use Drupal\registry\ToggleableComponentInterface;
use Drupal\registry\UrlComponentInterface;

/**
 * Dashboard form for registered components.
 *
 */
function registry_admin_form($form, &$form_state) {

  $has_disabled = FALSE;
  $components   = registry_get_components();

  foreach($components as $component_name => $info) {
    $component = new $info['class']();
    $details   = sprintf('%s (%s)', $info['name'], $component_name);

    $form[$component_name]['#tree'] = TRUE;

    if (registry_get_disabled_modules($component)) {
      $has_disabled = TRUE;
      $details .= "*";
    }

    $details .= '<div class="admin-requirements">' . t('Depends on: !modules', [
      '!modules' => implode(', ', _registry_get_decorated_module_list($component->getModuleDependencies())),
    ]) . '</div>';

    $form[$component_name]['name'] = [
      '#markup' => $details,
    ];
    $form[$component_name]['url'] = [
      '#markup' => $component instanceof UrlComponentInterface ? $component->getUrl() : t('N/A'),
    ];

    if ($component instanceof ToggleableComponentInterface) {
      $form[$component_name]['enabled'] = [
        '#type'    => 'radios',
        '#options' => [
          0 => t('No'),
          1 => t('Yes'),
        ],
        '#default_value' => (int) $component->isEnabled(),
      ];
    }
    else {
      $form[$component_name]['enabled'] = [
        '#markup' => t('Yes'),
      ];
    }

    $form[$component_name]['production'] = [
      '#markup' => $component->isProduction() ? t('Yes') : t('No'),
    ];
    $form[$component_name]['links'] = [
      '#markup' => $component instanceof ConfigurableComponentInterface ? l(t('Configure'), $component->getConfigUrl()) : '',
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

  foreach(registry_get_components() as $component_name => $info) {

    if (!isset($values[$component_name])) {
      continue;
    }

    $component = new $info['class']();

    if (!($component instanceof ToggleableComponentInterface)) {
      continue;
    }

    if (!empty($values[$component_name]['enabled'])) {
      $component->enable();
      $enabled[] = $info['name'];
    }
    else {
      $component->disable();
      $disabled[] = $info['name'];
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