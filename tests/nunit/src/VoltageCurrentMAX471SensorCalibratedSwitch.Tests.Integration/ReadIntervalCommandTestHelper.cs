using System;
namespace VoltageCurrentMAX471SensorCalibratedSwitch.Tests.Integration
{
	public class ReadIntervalCommandTestHelper : MeterHardwareTestHelper
	{
		public int ReadInterval = 1;

		public ReadIntervalCommandTestHelper()
		{
		}

		public void TestSetReadIntervalCommand()
		{
			WriteTitleText("Starting read interval command test");

			Console.WriteLine("Read interval: " + ReadInterval);

			ConnectDevices(false);

			SetDeviceReadInterval(ReadInterval);

			var dataEntry = WaitForDataEntry();

			AssertDataValueEquals(dataEntry, "V", ReadInterval);
		}
	}
}
