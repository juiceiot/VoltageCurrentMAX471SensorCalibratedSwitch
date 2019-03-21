#include <Arduino.h>
#include <EEPROM.h>
#include <duinocom.h>

#include "Common.h"
#include "VoltageCurrentMAX471Sensor.h"
#include "PowerSwitch.h"

#define SERIAL_MODE_CSV 1
#define SERIAL_MODE_QUERYSTRING 2

#define VERSION "1-0-0-1"

int serialMode = SERIAL_MODE_CSV;

void setup()
{
  Serial.begin(9600);

  Serial.println("Starting protected power switch");

  setupVoltageCurrentMAX471Sensor();

  setupPowerSwitch();

  serialOutputIntervalInSeconds = voltageCurrentMAX471SensorReadingIntervalInSeconds;

}

void loop()
{
// Disabled. Used for debugging
//  Serial.print(".");

  loopNumber++;

  serialPrintLoopHeader();

  checkCommand();

  takeVoltageCurrentMAX471SensorReading();

  serialPrintData();

  adjustPowerSwitch();

  serialPrintLoopFooter();

  delay(1);
}

/* Commands */
void checkCommand()
{
  if (isDebugMode)
  {
    Serial.println("Checking incoming serial commands");
  }

  if (checkMsgReady())
  {
    char* msg = getMsg();
        
    char letter = msg[0];

    int length = strlen(msg);

    Serial.print("Received message: ");
    Serial.println(msg);

    switch (letter)
    {
      case 'M':
        setSwitchMode(msg);
        break;
      case 'U':
        setMinVoltage(msg);
        break;
      case 'Y':
        setMaxVoltage(msg);
        break;
      case 'V':
        setVoltageCurrentMAX471SensorReadingInterval(msg);
        break;
      case 'X':
        restoreDefaultSettings();
        break;
      case 'Z':
        Serial.println("Toggling IsDebug");
        isDebugMode = !isDebugMode;
        break;
    }
    forceSerialOutput();
  }
  delay(1);
}

/* Settings */
void restoreDefaultSettings()
{
  Serial.println("Restoring default settings");

  restoreDefaultVoltageCurrentMAX471SensorSettings();
  restoreDefaultPowerSwitchSettings();
}

/* Serial Output */
void serialPrintData()
{
  bool isTimeToPrintData = lastSerialOutputTime + secondsToMilliseconds(serialOutputIntervalInSeconds) < millis()
      || lastSerialOutputTime == 0;

  bool isReadyToPrintData = isTimeToPrintData && voltageCurrentMAX471SensorReadingHasBeenTaken;

  if (isReadyToPrintData)
  {
    if (isDebugMode)
    {
      Serial.println("Printing serial data");
    }

    if (serialMode == SERIAL_MODE_CSV)
    {
      Serial.print("D;"); // This prefix indicates that the line contains data.
      Serial.print("VR:");
      Serial.print(voltageRaw);
      Serial.print(";");
      Serial.print("VC:");
      Serial.print(voltageCalibrated);
      Serial.print(";");
      Serial.print("CR:");
      Serial.print(currentRaw);
      Serial.print(";");
      Serial.print("CC:");
      Serial.print(currentCalibrated);
      Serial.print(";");
      Serial.print("U:");
      Serial.print(minVoltage);
      Serial.print(";");
      Serial.print("Y:");
      Serial.print(maxVoltage);
      Serial.print(";");
      Serial.print("M:");
      Serial.print(switchMode);
      Serial.print(";");
      Serial.print("I:");
      Serial.print(voltageCurrentMAX471SensorReadingIntervalInSeconds);
      Serial.print(";");
      Serial.print("PA:"); // Power available
      Serial.print(voltageCalibrated < minVoltage);
      Serial.print(";");
      Serial.print("SO:"); // Switch on
      Serial.print(switchIsOn);
      Serial.print(";");
      Serial.print("Z:");
      Serial.print(VERSION);
      Serial.print(";;");
      Serial.println();
    }
    /*else
    {
      Serial.print("raw=");
      Serial.print(voltageRaw);
      Serial.print("&");
      Serial.print("calibrated=");
      Serial.print(voltageCalibrated);
      Serial.print("&");
      Serial.print("minVoltage=");
      Serial.print(minVoltage);
      Serial.print("&");
      Serial.print("waterNeeded=");
      Serial.print(voltageCalibrated < minVoltage);
      Serial.print("&");
      Serial.print("switchMode=");
      Serial.print(switchMode);
      Serial.print("&");
      Serial.print("readingInterval=");
      Serial.print(voltageCurrentMAX471SensorReadingIntervalInSeconds);
      Serial.print("&");
      Serial.print("switchOn=");
      Serial.print(switchIsOn);
      Serial.print("&");
      Serial.print("secondsSinceSwitchOn=");
      Serial.print((millis() - lastSwitchFinishTime) / 1000);
      Serial.print("&");
      Serial.print("dry=");
      Serial.print(drySoilMoistureCalibrationValue);
      Serial.print("&");
      Serial.print("wet=");
      Serial.print(wetSoilMoistureCalibrationValue);
      Serial.print(";;");
      Serial.println();
    }*/

/*    if (isDebugMode)
    {
      Serial.print("Last switch start time:");
      Serial.println(switchStartTime);
      Serial.print("Last switch finish time:");
      Serial.println(lastSwitchFinishTime);
    }*/

    lastSerialOutputTime = millis();
  }
/*  else
  {
    if (isDebugMode)
    {    
      Serial.println("Not ready to serial print data");

      Serial.print("  Is time to serial print data: ");
      Serial.println(isTimeToPrintData);
      if (!isTimeToPrintData)
      {
        Serial.print("    Time remaining before printing data: ");
        Serial.print(millisecondsToSecondsWithDecimal(lastSerialOutputTime + secondsToMilliseconds(serialOutputIntervalInSeconds) - millis()));
        Serial.println(" seconds");
      }
      Serial.print("  Soil moisture sensor reading has been taken: ");
      Serial.println(voltageCurrentMAX471SensorReadingHasBeenTaken);
      Serial.print("  Is ready to print data: ");
      Serial.println(isReadyToPrintData);

    }
  }*/
}
