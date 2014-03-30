<?php

/**
 * A PHPUnit listener that sends test status updates through a serial device.
 * 
 * @package PHPUnit-NeoPixel-Indicator
 * @author Dan Ruscoe
 */
require 'vendor/autoload.php';

class PHPUnitIndicatorListener extends PHPUnit_Framework_BaseTestListener
{
	const SERIAL_PORT = '/dev/ttyUSB0';
	const TEST_STATUS_START = 'START';
	const TEST_STATUS_SUCCESS = 'SUCCESS';
	const TEST_STATUS_FAILURE = 'FAILURE';
	const SERIAL_DELIMITER = '|';

	/* @var $serialConnectionAvailable boolean */
	private $serialConnectionAvailable = false;
	/* @var $failedTests int */
	private $failedTests = 0;

	/**
	 * Constructor method sets up serial device connection.
	 */
	public function __construct()
	{
		$this->serial = new PhpSerial();
		$this->serialConnectionAvailable = $this->serial->deviceSet(self::SERIAL_PORT);

		if ($this->serialConnectionAvailable)
		{
			$this->serial->confBaudRate(9600);
			$this->serial->confParity('none');
			$this->serial->confCharacterLength(8);
			$this->serial->confStopBits(1);
			$this->serial->confFlowControl('none');
		}
	}

	public function startTestSuite(PHPUnit_Framework_TestSuite $suite)
	{
		$this->sendSerialMessage(self::TEST_STATUS_START);
	}

	public function endTestSuite(PHPUnit_Framework_TestSuite $suite)
	{
		if ($this->failedTests > 0)
		{
			$this->sendSerialMessage(self::TEST_STATUS_FAILURE);
		}
		else
		{
			$this->sendSerialMessage(self::TEST_STATUS_SUCCESS);
		}
	}

	public function addFailure(PHPUnit_Framework_Test $test, PHPUnit_Framework_AssertionFailedError $e, $time)
	{
		$this->failedTests++;
	}

	/**
	 * Sends a message over the connected serial device.
	 * 
	 * @param string $message The message to send.
	 */
	private function sendSerialMessage($message)
	{
		$this->serial->deviceOpen();
		$this->serial->sendMessage($message . self::SERIAL_DELIMITER);
		$this->serial->deviceClose();
	}

}

?>