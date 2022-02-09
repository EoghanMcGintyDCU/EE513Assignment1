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
	
	return 0;
}
