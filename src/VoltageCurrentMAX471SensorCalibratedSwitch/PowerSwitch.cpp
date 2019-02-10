#include <Arduino.h>

#include <EEPROM.h>

#include <duinocom.h>

#include "Common.h"
#include "VoltageCurrentMAX471Sensor.h"
#include "PowerSwitch.h"

// SLA/AGM settings
//float minVoltage = 11.8;
//float maxVoltage = 15;

// Custom settings
float minVoltage = 10;
float maxVoltage = 12;

float maxCurrent = 3;

bool switchIsOn = 0;
long switchStartTime = 0;
long lastSwitchFinishTime = 0;
int switchBurstOnTime = 3;
int switchBurstOffTime = 5;

int switchStatus = SWITCH_STATUS_AUTO;

#define minVoltageIsSetEEPROMFlagAddress 20
#define minVoltageEEPROMAddress 21

#define switchBurstOnTimeIsSetEEPROMFlagAddress 26
#define switchBurstOnTimeEEPROMAddress 27

#define switchBurstOffTimeIsSetEEPROMFlagAddress 33
#define switchBurstOffTimeEEPROMAddress 34

/* Setup */
void setupPowerSwitch()
{
  pinMode(SWITCH_PIN, OUTPUT);

  setupMinVoltage();
}

void setupMinVoltage()
{
  bool eepromIsSet = EEPROM.read(minVoltageIsSetEEPROMFlagAddress) == 99;

  if (eepromIsSet)
  {
    if (isDebugMode)
    	Serial.println("EEPROM read interval value has been set. Loading.");

    minVoltage = getMinVoltage();
  }
  else
  {
    if (isDebugMode)
      Serial.println("EEPROM read interval value has not been set. Using defaults.");
    
    //setMinVoltage(minVoltage);
  }
}

/* PowerSwitch */
void adjustPowerSwitch()
{
  if (isDebugMode)
  {
    Serial.println("Irrigating (if needed)");
  }

  if (switchStatus == SWITCH_STATUS_AUTO)
  {
    bool readingHasBeenTaken = lastVoltageCurrentMAX471SensorReadingTime > 0;
    bool voltageIsAboveMinimum = voltageRaw >= minVoltage;
    bool voltageIsBelowMaximum = voltageRaw <= maxVoltage;
    bool readingIsWithinRange = voltageIsAboveMinimum && voltageIsBelowMaximum;

    if (switchIsOn && !readingIsWithinRange)
    {
       switchOff();
    }
    else if (!switchIsOn && readingIsWithinRange)
    {
      switchOn();
    }
  }
  else if(switchStatus == SWITCH_STATUS_ON)
  {
    if (!switchIsOn)
      switchOn();
  }
  else
  {
    if (switchIsOn)
      switchOff();
  }
}

void switchOn()
{
  digitalWrite(SWITCH_PIN, HIGH);
  switchIsOn = true;

  switchStartTime = millis();
}

void switchOff()
{
  digitalWrite(SWITCH_PIN, LOW);
  switchIsOn = false;

  lastSwitchFinishTime = millis();
}

void setSwitchStatus(char* msg)
{
  int length = strlen(msg);

  if (length != 2)
  {
    Serial.println("Invalid switch status:");
    printMsg(msg);
  }
  else
  {
    int value = readInt(msg, 1, 1);

//    Serial.println("Value:");
//    Serial.println(value);

    setSwitchStatus(value);
  }
}

void setSwitchStatus(int newStatus)
{
  switchStatus = newStatus;
}

void setMinVoltage(char* msg)
{
  int length = strlen(msg);

  if (length == 1)
    setMinVoltageToCurrent();
  else
  {
    int value = readInt(msg, 1, length-1);

//    Serial.println("Value:");
//    Serial.println(value);

    setMinVoltage(value);
  }
}

void setMinVoltage(int newMinVoltage)
{
  minVoltage = newMinVoltage;

  if (isDebugMode)
  {
    Serial.print("Setting minVoltage to EEPROM: ");
    Serial.println(minVoltage);
  }

  EEPROM.write(minVoltageEEPROMAddress, newMinVoltage);
  
  setMinVoltageIsSetEEPROMFlag();
}

void setMinVoltageToCurrent()
{
  lastVoltageCurrentMAX471SensorReadingTime = 0;
  takeVoltageCurrentMAX471SensorReading();
  setMinVoltage(voltageCalibrated);
}

int getMinVoltage()
{
  int value = EEPROM.read(minVoltageEEPROMAddress);

  if (value <= 0
      || value >= 100)
    return minVoltage;
  else
  {
    int minVoltage = value; // Must multiply by 4 to get the original value

    if (isDebugMode)
    {
      Serial.print("MinVoltage found in EEPROM: ");
      Serial.println(minVoltage);
    }

    return minVoltage;
  }
}

void setMinVoltageIsSetEEPROMFlag()
{
  if (isDebugMode)
  {
    Serial.print("Setting EEPROM 'minVoltage is set flag'");
  }

  if (EEPROM.read(minVoltageIsSetEEPROMFlagAddress) != 99)
    EEPROM.write(minVoltageIsSetEEPROMFlagAddress, 99);
}


void setSwitchBurstOnTime(char* msg)
{
  int length = strlen(msg);

  if (length >= 2)
  {
    long value = readInt(msg, 1, length-1);

//    Serial.println("Value:");
//    Serial.println(value);

    setSwitchBurstOnTime(value);
  }
}

void setSwitchBurstOnTime(long newSwitchBurstOnTime)
{
  switchBurstOnTime = newSwitchBurstOnTime;

  if (isDebugMode)
  {
    Serial.print("Setting switchBurstOnTime to EEPROM: ");
    Serial.println(switchBurstOnTime);
  }

  EEPROMWriteLong(switchBurstOnTimeEEPROMAddress, switchBurstOnTime);

  setSwitchBurstOnTimeIsSetEEPROMFlag();
}

long getSwitchBurstOnTime()
{
  long value = EEPROMReadLong(switchBurstOnTimeEEPROMAddress);

  if (value == 0
      || value == 255)
    return switchBurstOnTime;
  else
  {
    int switchBurstOnTime = value;

    if (isDebugMode)
    {
      Serial.print("SwitchBurstOnTime found in EEPROM: ");
      Serial.println(switchBurstOnTime);
    }

    return switchBurstOnTime;
  }
}

void setSwitchBurstOnTimeIsSetEEPROMFlag()
{
  if (EEPROM.read(switchBurstOnTimeIsSetEEPROMFlagAddress) != 99)
    EEPROM.write(switchBurstOnTimeIsSetEEPROMFlagAddress, 99);
}


void setSwitchBurstOffTime(char* msg)
{
  int length = strlen(msg);

  if (length >= 2)
  {
    long value = readInt(msg, 1, length-1);

//    Serial.println("Value:");
//    Serial.println(value);

    setSwitchBurstOffTime(value);
  }
}

void setSwitchBurstOffTime(long newSwitchBurstOffTime)
{
  if (isDebugMode)
  {
    Serial.print("Setting switch burst off time to EEPROM: ");
    Serial.println(newSwitchBurstOffTime);
  }

  EEPROMWriteLong(switchBurstOffTimeEEPROMAddress, newSwitchBurstOffTime);

  setSwitchBurstOffTimeIsSetEEPROMFlag();

  switchBurstOffTime = newSwitchBurstOffTime;
}

long getSwitchBurstOffTime()
{

  if (EEPROM.read(switchBurstOffTimeIsSetEEPROMFlagAddress) == 99)
  {
    long value = EEPROMReadLong(switchBurstOffTimeEEPROMAddress);
    
    if (value < 0 || value > 9999)
    {
      value = switchBurstOffTime;
    }

//    Serial.println("Value:");
//    Serial.println(value);

    return value;
  }
  else
    return switchBurstOffTime;
}

void setSwitchBurstOffTimeIsSetEEPROMFlag()
{
  if (EEPROM.read(switchBurstOffTimeIsSetEEPROMFlagAddress) != 99)
    EEPROM.write(switchBurstOffTimeIsSetEEPROMFlagAddress, 99);
}

/* Restore defaults */
void restoreDefaultPowerSwitchSettings()
{
  Serial.println("Reset default settings");

  restoreDefaultMinVoltage();
  restoreDefaultSwitchBurstOnTime();
}

void restoreDefaultMinVoltage()
{
  Serial.println("Reset minVoltage");

  removeMinVoltageEEPROMIsSetFlag();

  minVoltage = 30;

  setMinVoltage(minVoltage);
}

void restoreDefaultSwitchBurstOnTime()
{
  Serial.println("Reset switch burst on time");

  removeSwitchBurstOnTimeEEPROMIsSetFlag();

  switchBurstOnTime = 3;

  setSwitchBurstOnTime(switchBurstOnTime);
}

void restoreDefaultSwitchBurstOffTime()
{
  Serial.println("Reset switch burst off time");

  removeSwitchBurstOffTimeEEPROMIsSetFlag();

  switchBurstOffTime = 5;

  setSwitchBurstOffTime(switchBurstOffTime);
}

void removeMinVoltageEEPROMIsSetFlag()
{
    EEPROM.write(minVoltageIsSetEEPROMFlagAddress, 0);
}

void removeSwitchBurstOnTimeEEPROMIsSetFlag()
{
    EEPROM.write(switchBurstOnTimeIsSetEEPROMFlagAddress, 0);
}
