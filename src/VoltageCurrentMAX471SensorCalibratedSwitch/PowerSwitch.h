#ifndef IRRIGATION_H_
#define IRRIGATION_H_

#include <Arduino.h>

#define SWITCH_PIN 11

#define SWITCH_STATUS_OFF 0
#define SWITCH_STATUS_ON 1
#define SWITCH_STATUS_AUTO 2

extern float minVoltage;
extern float maxVoltage;
extern bool switchIsOn;
extern long switchStartTime;
extern long lastSwitchFinishTime;
extern int switchBurstOnTime;
extern int switchBurstOffTime;
extern int switchStatus;
extern int minVoltageIsSetEEPROMFlagAddress;
extern int minVoltageEEPROMAddress;
extern int switchBurstOnTimeIsSetEEPROMFlagAddress;
extern int switchBurstOnTimeEEPROMAddress;
extern int switchBurstOffTimeIsSetEEPROMFlagAddress;
extern int switchBurstOffTimeEEPROMAddress;

void setupPowerSwitch();
void setupMinVoltage();
void setupSwitchBurstOnTime();
void setupSwitchBurstOffTime();
void adjustPowerSwitch();
void switchOn();
void switchOff();

void setSwitchStatus(char* msg);
void setSwitchStatus(int newStatus);

void setMinVoltage(char* msg);
void setMinVoltage(int newMinVoltage);
void setMinVoltageToCurrent();
int getMinVoltage();
void setMinVoltageIsSetEEPROMFlag();

void setSwitchBurstOnTime(char* msg);
void setSwitchBurstOnTime(long newSwitchBurstOnTime);
long getSwitchBurstOnTime();
void setSwitchBurstOnTimeIsSetEEPROMFlag();
void removeSwitchBurstOnTimeEEPROMIsSetFlag();

void setSwitchBurstOffTime(char* msg);
void setSwitchBurstOffTime(long newSwitchBurstOffTime);
long getSwitchBurstOffTime();
void setSwitchBurstOffTimeIsSetEEPROMFlag();
void removeSwitchBurstOffTimeEEPROMIsSetFlag();


void removeMinVoltageEEPROMIsSetFlag();
void restoreDefaultMinVoltage();
void restoreDefaultPowerSwitchSettings();
void restoreDefaultSwitchBurstOnTime();
void restoreDefaultSwitchBurstOffTime();
#endif
/* IRRIGATION_H_ */
