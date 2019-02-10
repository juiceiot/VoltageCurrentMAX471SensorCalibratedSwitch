using System;
using System.Threading;

namespace VoltageCurrentMAX471SensorCalibratedSwitch.Tests.Integration
{
	public class CalibrateCommandTestHelper : MeterHardwareTestHelper
	{
		public string Label;
		public string Letter;
		public int SimulatedVoltagePercentage = -1;
		public int RawVoltageValue = 0;

		public CalibrateCommandTestHelper()
		{
		}

		public void TestCalibrateCommand()
		{
			WriteTitleText("Starting calibrate " + Label + " command test");

			Console.WriteLine("Simulated voltage: " + SimulatedVoltagePercentage + "%");

			if (RawVoltageValue == 0)
				RawVoltageValue = SimulatedVoltagePercentage * AnalogPinMaxValue / 100;

			Console.WriteLine("Raw voltage value: " + RawVoltageValue);
			Console.WriteLine("");

			var simulatorIsNeeded = SimulatedVoltagePercentage > -1;

			ConnectDevices(simulatorIsNeeded);

			if (SimulatorIsEnabled)
			{
				SimulateVoltage(SimulatedVoltagePercentage);

				var values = WaitForData(3); // Wait for 3 data entries to give the simulator time to stabilise

				AssertDataValueIsWithinRange(values[values.Length - 1], "R", RawVoltageValue, RawValueMarginOfError);
			}

			SendCalibrationCommand();
		}

		public void SendCalibrationCommand()
		{
			var command = Letter;

			// If the simulator isn't enabled then the raw value is passed as part of the command to specify it directly
			if (!SimulatorIsEnabled)
				command = command + RawVoltageValue;

			SendDeviceCommand(command);

			var data = WaitForData(3); // Wait for 3 data entries to let the voltage simulator stabilise

			// If using the voltage simulator then the value needs to be within a specified range
			if (SimulatorIsEnabled)
				AssertDataValueIsWithinRange(data[data.Length - 1], Letter, RawVoltageValue, RawValueMarginOfError);
			else // Otherwise it needs to be exact
				AssertDataValueEquals(data[data.Length - 1], Letter, RawVoltageValue);
		}
	}
}