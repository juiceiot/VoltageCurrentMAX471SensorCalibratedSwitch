﻿using System;
namespace VoltageCurrentMAX471SensorCalibratedSwitch.Tests.Integration
{
	public class SerialOutputTimeTestHelper : MeterHardwareTestHelper
	{
		public int ReadInterval = 1;

		public void TestSerialOutputTime()
		{
			WriteTitleText("Starting serial output time test");

			Console.WriteLine("Read interval: " + ReadInterval);

			ConnectDevices(false);

			SetDeviceReadInterval(ReadInterval);

			ReadFromDeviceAndOutputToConsole();

			// Wait for the first data line before starting
			WaitUntilDataLine();

			// Get the time until the next data line
			var secondsBetweenDataLines = WaitUntilDataLine();

			var expectedTimeBetweenDataLines = ReadInterval;

			Console.WriteLine("Time between data lines: " + secondsBetweenDataLines + " seconds");

			AssertIsWithinRange("serial output time", expectedTimeBetweenDataLines, secondsBetweenDataLines, TimeErrorMargin);
		}
	}
}
