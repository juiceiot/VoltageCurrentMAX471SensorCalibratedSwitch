using System;
using System.Collections.Generic;
using System.Threading;
using NUnit.Framework;
namespace VoltageCurrentMAX471SensorCalibratedSwitch.Tests.Integration
{
	public class SwitchTestHelper : ProtectorHardwareTestHelper
	{
		public SwitchStatus SwitchCommand = SwitchStatus.Auto;
		public int SimulatedVoltagePercentage = 50;
		public int BurstOnTime = 3;
		public int BurstOffTime = 3;
		public int Threshold = 30;
		public int DurationToCheckSwitch = 5;

		public void TestSwitch()
		{
			WriteTitleText("Starting switch test");

			Console.WriteLine("Switch command: " + SwitchCommand);
			Console.WriteLine("Simulated voltage: " + SimulatedVoltagePercentage + "%");
			Console.WriteLine("");

			ConnectDevices();

			var cmd = "P" + (int)SwitchCommand;

			SendDeviceCommand(cmd);

			SendDeviceCommand("B" + BurstOnTime);
			SendDeviceCommand("O" + BurstOffTime);
			SendDeviceCommand("T" + Threshold);

			SimulateVoltage(SimulatedVoltagePercentage);

			var data = WaitForData(3);

			CheckDataValues(data[data.Length - 1]);
		}

		public void CheckDataValues(Dictionary<string, string> dataEntry)
		{
			AssertDataValueEquals(dataEntry, "P", (int)SwitchCommand);
			AssertDataValueEquals(dataEntry, "B", BurstOnTime);
			AssertDataValueEquals(dataEntry, "O", BurstOffTime);
			AssertDataValueEquals(dataEntry, "T", Threshold);

			// TODO: Check PO value matches the switch

			AssertDataValueIsWithinRange(dataEntry, "C", SimulatedVoltagePercentage, CalibratedValueMarginOfError);

			switch (SwitchCommand)
			{
				case SwitchStatus.Off:
					CheckSwitchIsOff();
					break;
				case SwitchStatus.On:
					CheckSwitchIsOn();
					break;
				case SwitchStatus.Auto:
					CheckSwitchIsAuto();
					break;
			}
		}

		public void CheckSwitchIsOff()
		{
			AssertSimulatorPinForDuration("switch", SimulatorSwitchPin, false, DurationToCheckSwitch);
		}

		public void CheckSwitchIsOn()
		{
			AssertSimulatorPinForDuration("switch", SimulatorSwitchPin, true, DurationToCheckSwitch);
		}

		public void CheckSwitchIsAuto()
		{
			var waterIsNeeded = SimulatedVoltagePercentage < Threshold;

			if (waterIsNeeded)
			{
				var switchStaysOn = BurstOffTime == 0;

				if (switchStaysOn)
				{
					CheckSwitchIsOn();
				}
				else
				{
					// Wait for the switch to turn on for the first time
					WaitUntilSimulatorPinIs("switch", SimulatorSwitchPin, true);

					// Check on time     
					var timeOn = WaitWhileSimulatorPinIs("switch", SimulatorSwitchPin, true);
					AssertIsWithinRange("switch", BurstOnTime, timeOn, TimeErrorMargin);

					// Check off time
					var timeOff = WaitWhileSimulatorPinIs("switch", SimulatorSwitchPin, false);
					AssertIsWithinRange("switch", BurstOffTime, timeOff, TimeErrorMargin);

					// Check on time
					timeOn = WaitWhileSimulatorPinIs("switch", SimulatorSwitchPin, true);
					AssertIsWithinRange("switch", BurstOnTime, timeOn, TimeErrorMargin);

					// Check off time
					timeOff = WaitWhileSimulatorPinIs("switch", SimulatorSwitchPin, false);
					AssertIsWithinRange("switch", BurstOffTime, timeOff, TimeErrorMargin);
				}
			}
			else
			{
				CheckSwitchIsOff();
			}
		}
	}
}