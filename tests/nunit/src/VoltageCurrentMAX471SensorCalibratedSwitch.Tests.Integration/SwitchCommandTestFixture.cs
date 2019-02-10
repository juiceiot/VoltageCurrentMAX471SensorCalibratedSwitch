using System;
using NUnit.Framework;
using duinocom;
using System.Threading;
using ArduinoSerialControllerClient;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.IO.Ports;

namespace VoltageCurrentMAX471SensorCalibratedSwitch.Tests.Integration
{
	[TestFixture(Category = "Integration")]
	public class SwitchCommandTestFixture : BaseTestFixture
	{
		[Test]
		public void Test_SetSwitchToOn()
		{
			using (var helper = new SwitchCommandTestHelper())
			{
				helper.SwitchCommand = SwitchStatus.On;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestSwitchCommand();
			}
		}

		[Test]
		public void Test_SetSwitchToOff()
		{
			using (var helper = new SwitchCommandTestHelper())
			{
				helper.SwitchCommand = SwitchStatus.Off;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestSwitchCommand();
			}
		}

		[Test]
		public void Test_SetSwitchToAuto()
		{
			using (var helper = new SwitchCommandTestHelper())
			{
				helper.SwitchCommand = SwitchStatus.Auto;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestSwitchCommand();
			}
		}
	}
}
