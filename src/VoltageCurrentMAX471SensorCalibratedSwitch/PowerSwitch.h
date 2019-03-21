#ifndef IRRIGATION_H_
#define IRRIGATION_H_

#include <Arduino.h>

#define SWITCH_PIN 11

#define SWITCH_MODE_OFF 0
#define SWITCH_MODE_ON 1
#define SWITCH_MODE_AUTO 2

extern float minVoltage;
extern float maxVoltage;
extern bool switchIsOn;
extern long switchStartTime;
extern long lastSwitchFinishTime;
extern int switchMode;
extern int minVoltageIsSetEEPROMFlagAddress;
extern int minVoltageEEPROMAddress;
extern int maxVoltageIsSetEEPROMFlagAddress;
extern int maxVoltageEEPROMAddress;

void setupPowerSwitch();
void setupMinVoltage();
void setupMaxVoltage();
void adjustPowerSwitch();
void switchOn();
void switchOff();

void setSwitchMode(char* msg);
void setSwitchMode(int newStatus);

void setMinVoltage(char* msg);
void setMinVoltage(int newMinVoltage);
int getMinVoltage();
void setMinVoltageIsSetEEPROMFlag();

void setMaxVoltage(char* msg);
void setMaxVoltage(int newMinVoltage);
int getMaxVoltage();
void setMaxVoltageIsSetEEPROMFlag();

void restoreDefaultMinVoltage();
void restoreDefaultPowerSwitchSettings();
#endif
/* IRRIGATION_H_ */
