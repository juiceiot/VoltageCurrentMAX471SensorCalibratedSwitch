using System;

namespace VoltageCurrentMAX471SensorCalibratedSwitch.Tests.Integration
{
	public class CalibrationEEPROMTestHelper : ProtectorHardwareTestHelper
	{
		public string Label;
		public string Letter;
		public int RawVoltageValue = 0;

		public void TestCalibrationEEPROM()
		{
			WriteTitleText("Starting calibration command test");

			Console.WriteLine("Label: " + Label);
			Console.WriteLine("Letter: " + Letter);
			Console.WriteLine("");

			ConnectDevices();

			ResetDeviceSettings ();

			SendCalibrationCommand();

			ResetDeviceViaPin ();

			var dataEntry = WaitForDataEntry ();

			AssertDataValueEquals(dataEntry, Letter, RawVoltageValue);
		}

		public void SendCalibrationCommand()
		{
			var command = Letter + RawVoltageValue;

			WriteParagraphTitleText("Sending calibration command...");

			SendDeviceCommand(command);

			var dataEntry = WaitForDataEntry();

			WriteParagraphTitleText("Checking calibration value...");

			AssertDataValueEquals(dataEntry, Letter, RawVoltageValue);
		}
	}
}
