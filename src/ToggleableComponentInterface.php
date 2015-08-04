<?php

namespace Drupal\registry;


/**
 * The interface for registered components that can be toggled on and off.
 *
 */
interface ToggleableComponentInterface extends ComponentInterface {

  /**
   * Enables this component.
   *
   * @return void
   *
   */
  public function enable();

  /**
   * Disables this component.
   *
   * @return void
   *
   */
  public function disable();

  /**
   * Determines if the component is currently enabled or not.
   *
   * @return boolean
   *
   */
  public function isEnabled();

}
