<?php

namespace Drupal\registry;


/**
 * The interface for registered components.
 *
 */
interface ComponentInterface {

  /**
   * Determines if the component's configuration is considered "production
   * mode".
   *
   * @return boolean
   *
   */
  public function isProduction();

  /**
   * Returns a list of modules that this component represents.
   *
   * @return array
   *
   */
  public function getModuleDependencies();

}
