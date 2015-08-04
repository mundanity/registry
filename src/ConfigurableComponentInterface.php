<?php

namespace Drupal\registry;


/**
 * The interface for registered components that can be configured.
 *
 */
interface ConfigurableComponentInterface extends ComponentInterface {

  /**
   * Returns the URL to the configuration page for this component.
   *
   * @return string
   *
   */
  public function getConfigUrl();

}
