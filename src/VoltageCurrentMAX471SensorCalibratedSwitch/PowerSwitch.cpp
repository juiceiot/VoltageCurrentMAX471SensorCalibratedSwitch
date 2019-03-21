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

int switchMode = SWITCH_MODE_AUTO;

#define minVoltageIsSetEEPROMFlagAddress 20
#define minVoltageEEPROMAddress 21

#define maxVoltageIsSetEEPROMFlagAddress 24
#define maxVoltageEEPROMAddress 25

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

  if (switchMode == SWITCH_MODE_AUTO)
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
  else if(switchMode == SWITCH_MODE_ON)
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

void setSwitchMode(char* msg)
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

    setSwitchMode(value);
  }
}

void setSwitchMode(int newStatus)
{
  switchMode = newStatus;
}

void setMinVoltage(char* msg)
{
  int length = strlen(msg);

  if (length > 1)
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
void setMaxVoltage(char* msg)
{
  int length = strlen(msg);

  if (length > 1)
  {
    int value = readInt(msg, 1, length-1);

//    Serial.println("Value:");
//    Serial.println(value);

    setMaxVoltage(value);
  }
}

void setMaxVoltage(int newMaxVoltage)
{
  maxVoltage = newMaxVoltage;

  if (isDebugMode)
  {
    Serial.print("Setting maxVoltage to EEPROM: ");
    Serial.println(maxVoltage);
  }

  EEPROM.write(maxVoltageEEPROMAddress, newMaxVoltage);
  
  setMaxVoltageIsSetEEPROMFlag();
}

int getMaxVoltage()
{
  int value = EEPROM.read(maxVoltageEEPROMAddress);

  if (value <= 0
      || value >= 100)
    return maxVoltage;
  else
  {
    int maxVoltage = value; // Must multiply by 4 to get the original value

    if (isDebugMode)
    {
      Serial.print("MaxVoltage found in EEPROM: ");
      Serial.println(maxVoltage);
    }

    return maxVoltage;
  }
}

void setMaxVoltageIsSetEEPROMFlag()
{
  if (isDebugMode)
  {
    Serial.print("Setting EEPROM 'maxVoltage is set flag'");
  }

  if (EEPROM.read(maxVoltageIsSetEEPROMFlagAddress) != 99)
    EEPROM.write(maxVoltageIsSetEEPROMFlagAddress, 99);
}


/* Restore defaults */
void restoreDefaultPowerSwitchSettings()
{
  Serial.println("Reset default settings");

  restoreDefaultMinVoltage();
}

void restoreDefaultMinVoltage()
{
  Serial.println("Reset minVoltage");

  removeEEPROMFlag(minVoltageIsSetEEPROMFlagAddress);

  minVoltage = 30;

  setMinVoltage(minVoltage);
}

void removeMinVoltageEEPROMIsSetFlag()
{
    EEPROM.write(minVoltageIsSetEEPROMFlagAddress, 0);
}

