#include <iostream> 
#include "RTC.h"

int main()
{
	RTC rtc;
	std::cout << "Reading current time" << std::endl;
	rtc.displayTime();
	
	std::cout << "Reading current temperature" << std::endl;
	rtc.displayTemperature();
	
	std::cout << "Setting time & date" << std::endl;
	rtc.setDate(30,51,21,2,15,2,22);
	rtc.displayTime();
	rtc.displayDate();

	std::cout << "Setting Alarm 1" << std::endl;
	rtc.setAlarm1(00,30,22);
	std::cout << "Reading Alarm 1" << std::endl;
	rtc.readAlarm1();
	
	std::cout << "Setting Alarm 2" << std::endl;
	rtc.setAlarm2(45,22,3);
	std::cout << "Reading Alarm 2" << std::endl;
	rtc.readAlarm2();	

	std::cout << "Running Alarm test" << std::endl;
	rtc.alarmTest();

	std::cout << "Setting Square Wave" << std::endl;
	rtc.setSquareWave(freq4);

	std::cout << "Novel functionality" << std::endl;
	rtc.novel();

	return 0;
}
