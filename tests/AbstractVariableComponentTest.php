<?php


/**
 * Tests for our AbstractVariableComponent class.
 *
 */
class AbstractVariableComponentTest extends PHPUnit_Framework_TestCase {

  public function setUp() {
    $this->component = $this->getMockForAbstractClass('Drupal\registry\AbstractVariableComponent');
    $this->component
      ->expects($this->any())
      ->method('getUrlVariable')
      ->will($this->returnValue('test_url'));
    $this->component
      ->expects($this->any())
      ->method('getEnabledVariable')
      ->will($this->returnValue('test_enabled'));
  }


  public function tearDown() {
    variable_del('test_url');
    variable_del('test_enabled');
  }


  public function testGetUrlReturnsDefaultValue() {
    $this->assertEquals('http://localhost', $this->component->getUrl());
  }


  public function testGetUrlReturnsSetValue() {
    variable_set('test_url', 'http://test.com');
    $this->assertEquals('http://test.com', $this->component->getUrl());
  }


  public function testIsEnabledDefaultIsFalse() {
    $this->assertFalse($this->component->isEnabled());
  }


  public function testIsEnabledIsTrue() {
    variable_set('test_enabled', 1);
    $this->assertTrue($this->component->isEnabled());
  }


  public function testEnableActuallyEnables() {
    $this->component->enable();
    $this->assertTrue($this->component->isEnabled());
  }


  public function testDisableActuallyDisables() {
    $this->component->disable();
    $this->assertFalse($this->component->isEnabled());
  }


  public function testUrlDefaultIsLocalhost() {
    $this->assertEquals('http://localhost', $this->component->getUrlDefaultValue());
  }


  public function testEnabledValueIsTrue() {
    $this->assertTrue($this->component->getEnabledValue());
  }


  public function testDisabledValueIsFalse() {
    $this->assertFalse($this->component->getDisabledValue());
  }

}


// The AbstractVariableComponent is dependant on Drupal functions, so we'll mock
// the behaviour of variable_get/set to avoid worrying about a bootstrap.
$variables = array();

function variable_set($name, $value) {
  global $variables;
  $variables[$name] = $value;
}

function variable_get($name, $default) {
  global $variables;
  return isset($variables[$name]) ? $variables[$name] : $default;
}

function variable_del($name) {
  global $variables;
  if (isset($variables[$name])) {
    unset($variables[$name]);
  }
}