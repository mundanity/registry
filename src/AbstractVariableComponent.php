<?php

namespace Drupal\registry;


/**
 * A base class for a component that is handled primarily through the use of
 * Drupal variables.
 *
 */
abstract class AbstractVariableComponent implements ComponentInterface {

  /**
   * {@inheritdoc}
   *
   */
  public function getUrl() {
    return variable_get($this->getUrlVariable(), $this->getUrlDefaultValue());
  }


  /**
   * {@inheritdoc}
   *
   */
  public function getConfigUrl() {}


  /**
   * {@inheritdoc}
   *
   */
  public function isEnabled() {
    return (variable_get($this->getEnabledVariable(), $this->getDisabledValue()) == $this->getEnabledValue());
  }


  /**
   * {@inheritdoc}
   *
   */
  abstract public function isProduction();


  /**
   * {@inheritdoc}
   *
   */
  public function enable() {
    variable_set($this->getEnabledVariable(), $this->getEnabledValue());
  }


  /**
   * {@inheritdoc}
   *
   */
  public function disable() {
    variable_set($this->getEnabledVariable(), $this->getDisabledValue());
  }


  /**
   * {@inheritdoc}
   *
   */
  abstract public function getModuleDependencies();


  /**
   * Returns the default value for the Drupal variable used for the URL for the
   * component.
   *
   * @return string
   *
   */
  public function getUrlDefaultValue() {
    return 'http://localhost';
  }


  /**
   * Returns the value to use to set the "enabled" value to TRUE.
   *
   * @return mixed
   *
   */
  public function getEnabledValue() {
    return TRUE;
  }


  /**
   * Returns the value to use to set the "enabled" value to FALSE.
   *
   * @return mixed
   *
   */
  public function getDisabledValue() {
    return FALSE;
  }


  /**
   * Returns the Drupal variable used for the URL for the component.
   *
   * @return string
   *
   */
  abstract protected function getUrlVariable();


  /**
   * Returns the Drupal variable use to determine whether the component is
   * enabled or not.
   *
   * @return string
   *
   */
  abstract protected function getEnabledVariable();

}