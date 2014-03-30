<?php

/**
 * An example unit test to demonstate failure notification in the listener.
 * 
 * @package PHPUnit-NeoPixel-Indicator
 * @author Dan Ruscoe
 */
class ExampleFailureTest extends PHPUnit_Framework_TestCase
{

	/**
	 * A unit test designed to always fail.
	 */
	public function testFailure()
	{
		$this->assertTrue(false);
	}

}

?>
