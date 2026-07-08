#pragma once

#include <iostream>
#include <windows.h>
#include <powrprof.h>

#pragma comment(lib, "PowrProf.lib")
#pragma comment (lib, "setupapi.lib")

#include <thread>   
#include "conio.h"
#include <Poclass.h>
#include <Setupapi.h>
#include <devguid.h>

class Battery
{
private:
	std::string energyType;
	std::string batteryType;
	uint8_t percent;
	std::string energySavingMode;
	std::string timeRemaining;
	uint64_t timeAfterChargingOff;
	bool isCharging;
public:
	Battery();
	std::string getEnergyType(SYSTEM_POWER_STATUS sps);
	std::string getBatteryType();
	void processTimeAfterChargingOff(SYSTEM_POWER_STATUS sps);
	void printTimeAfterChargingOff();
	uint8_t getPercent(SYSTEM_POWER_STATUS sps);
	std::string getEnergySavingMode(SYSTEM_POWER_STATUS sps);
	std::string getTimeRemaining(SYSTEM_POWER_STATUS sps);
	void setBatteryInfo();
	void printBatteryInfo();

	void writeBatteryInfoToFile(const std::string& filename);
};