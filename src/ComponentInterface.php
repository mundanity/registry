<?php

namespace Drupal\registry;


/**
 * The interface for registered components.
 *
 */
interface ComponentInterface {

  /**
   * Returns a list of modules that this component represents.
   *
   * @return array
   *
   */
  public function getModuleDependencies();

}
