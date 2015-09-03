<?php

namespace Drupal\registry;


/**
 * The interface for registered components that have a service URL.
 *
 */
interface UrlComponentInterface extends ComponentInterface {

  /**
   * Returns the URL to the component's underlying service.
   *
   * @return string
   *
   */
  public function getUrl();

}
