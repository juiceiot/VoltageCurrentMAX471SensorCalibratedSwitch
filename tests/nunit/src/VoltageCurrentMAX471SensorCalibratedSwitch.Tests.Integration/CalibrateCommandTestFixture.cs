using NUnit.Framework;

namespace VoltageCurrentMAX471SensorCalibratedSwitch.Tests.Integration
{
	[TestFixture(Category = "Integration")]
	public class CalibrateCommandTestFixture : BaseTestFixture
	{
		[Test]
		public void Test_CalibrateDryToCurrentVoltageValueCommand_20Percent()
		{
			using (var helper = new CalibrateCommandTestHelper())
			{
				helper.Label = "dry";
				helper.Letter = "D";
				helper.SimulatedVoltagePercentage = 20;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestCalibrateCommand();
			}
		}

		[Test]
		public void Test_CalibrateDryToCurrentVoltageValueCommand_30Percent()
		{
			using (var helper = new CalibrateCommandTestHelper())
			{
				helper.Label = "dry";
				helper.Letter = "D";
				helper.SimulatedVoltagePercentage = 30;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestCalibrateCommand();
			}
		}

		[Test]
		public void Test_CalibrateDryToSpecifiedValueCommand_200()
		{
			using (var helper = new CalibrateCommandTestHelper())
			{
				helper.Label = "dry";
				helper.Letter = "D";
				helper.RawVoltageValue = 200;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestCalibrateCommand();
			}
		}

		[Test]
		public void Test_CalibrateDryToSpecifiedValueCommand_220()
		{
			using (var helper = new CalibrateCommandTestHelper())
			{
				helper.Label = "dry";
				helper.Letter = "D";
				helper.RawVoltageValue = 220;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestCalibrateCommand();
			}
		}

		[Test]
		public void Test_CalibrateWetToCurrentVoltageValueCommand_80Percent()
		{
			using (var helper = new CalibrateCommandTestHelper())
			{
				helper.Label = "wet";
				helper.Letter = "W";
				helper.SimulatedVoltagePercentage = 80;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestCalibrateCommand();
			}
		}

		[Test]
		public void Test_CalibrateWetToCurrentVoltageValueCommand_90Percent()
		{
			using (var helper = new CalibrateCommandTestHelper())
			{
				helper.Label = "wet";
				helper.Letter = "W";
				helper.SimulatedVoltagePercentage = 90;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestCalibrateCommand();
			}
		}

		[Test]
		public void Test_CalibrateWetToSpecifiedValueCommand_880()
		{
			using (var helper = new CalibrateCommandTestHelper())
			{
				helper.Label = "wet";
				helper.Letter = "W";
				helper.RawVoltageValue = 880;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestCalibrateCommand();
			}
		}

		[Test]
		public void Test_CalibrateWetToSpecifiedValueCommand_900()
		{
			using (var helper = new CalibrateCommandTestHelper())
			{
				helper.Label = "wet";
				helper.Letter = "W";
				helper.RawVoltageValue = 900;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestCalibrateCommand();
			}
		}
	}
}
