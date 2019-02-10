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
	public class SwitchTestFixture : BaseTestFixture
	{
		[Test]
		public void Test_SwitchOn()
		{
			using (var helper = new SwitchTestHelper())
			{
				helper.SwitchCommand = SwitchStatus.On;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestSwitch();
			}
		}

		[Test]
		public void Test_SwitchOff()
		{
			using (var helper = new SwitchTestHelper())
			{
				helper.SwitchCommand = SwitchStatus.Off;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestSwitch();
			}
		}

		[Test]
		public void Test_SwitchAuto_WaterNeeded_Burst1Off0()
		{
			using (var helper = new SwitchTestHelper())
			{
				helper.SwitchCommand = SwitchStatus.Auto;
				helper.SimulatedVoltagePercentage = 10;
				helper.BurstOnTime = 1;
				helper.BurstOffTime = 0;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestSwitch();
			}
		}

		[Test]
		public void Test_SwitchAuto_WaterNeeded_Burst1Off1()
		{
			using (var helper = new SwitchTestHelper())
			{
				helper.SwitchCommand = SwitchStatus.Auto;
				helper.SimulatedVoltagePercentage = 10;
				helper.BurstOnTime = 1;
				helper.BurstOffTime = 1;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestSwitch();
			}
		}

		[Test]
		public void Test_SwitchAuto_WaterNeeded_Burst1Off2()
		{
			using (var helper = new SwitchTestHelper())
			{
				helper.SwitchCommand = SwitchStatus.Auto;
				helper.SimulatedVoltagePercentage = 10;
				helper.BurstOnTime = 1;
				helper.BurstOffTime = 2;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestSwitch();
			}
		}

		[Test]
		public void Test_SwitchAuto_WaterNotNeeded()
		{
			using (var helper = new SwitchTestHelper())
			{
				helper.SwitchCommand = SwitchStatus.Auto;
				helper.SimulatedVoltagePercentage = 80;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestSwitch();
			}
		}
	}
}
