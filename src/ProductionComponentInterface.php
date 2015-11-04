<?php

namespace Drupal\registry;


/**
 * The interface for registered components that can have a "production mode".
 *
 */
interface ProductionComponentInterface extends ComponentInterface {

  /**
   * Determines if the component's is considered in "production mode".
   *
   * @return boolean
   *
   */
  public function isProduction();
}
