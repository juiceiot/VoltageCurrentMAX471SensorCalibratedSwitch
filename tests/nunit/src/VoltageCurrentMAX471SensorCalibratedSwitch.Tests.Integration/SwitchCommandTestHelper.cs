using System;
namespace VoltageCurrentMAX471SensorCalibratedSwitch.Tests.Integration
{
	public class SwitchCommandTestHelper : ProtectorHardwareTestHelper
	{
		public SwitchStatus SwitchCommand = SwitchStatus.Auto;

		public void TestSwitchCommand()
		{
			WriteTitleText("Starting switch command test");

			Console.WriteLine("Switch command: " + SwitchCommand);
			Console.WriteLine("");

			ConnectDevices(false);

			var cmd = "P" + (int)SwitchCommand;

			SendDeviceCommand(cmd);

			var dataEntry = WaitForDataEntry();
			dataEntry = WaitForDataEntry();
			AssertDataValueEquals(dataEntry, "P", (int)SwitchCommand);
		}
	}
}