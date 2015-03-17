<?php

namespace Drupal\registry;


/**
 * The interface for registered components.
 *
 */
interface ComponentInterface {

  /**
   * Returns the URL to the registered component.
   *
   * @return string
   *
   */
  public function getUrl();


  /**
   * Returns the URL to the configuration page for this component, if it exists.
   *
   * @return string
   *
   */
  public function getConfigUrl();


  /**
   * Determines if the component is currently enabled or not.
   *
   * @return boolean
   *
   */
  public function isEnabled();


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
   * Returns a list of modules that this component represents.
   *
   * @return array
   *
   */
  public function getModuleDependencies();

}