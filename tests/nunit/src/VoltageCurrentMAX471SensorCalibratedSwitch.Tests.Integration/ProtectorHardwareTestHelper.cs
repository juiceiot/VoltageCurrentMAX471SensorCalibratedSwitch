using System;

namespace VoltageCurrentMAX471SensorCalibratedSwitch.Tests.Integration
{
	public class ProtectorHardwareTestHelper : MeterHardwareTestHelper
	{
		public int SimulatorSwitchPin = 2;

		public ProtectorHardwareTestHelper()
		{
		}

		public override void PrepareDeviceForTest(bool consoleWriteDeviceOutput)
		{
			base.PrepareDeviceForTest(false);

			if (consoleWriteDeviceOutput)
				ReadFromDeviceAndOutputToConsole();
		}
	}
}
