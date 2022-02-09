#include <iostream> 
#include "RTC.h"

int main()
{
	RTC rtc;
	std::cout << "Reading current time" << std::endl;
	rtc.displayTime();
	
	std::cout << "Reading current temperature" << std::endl;
	rtc.displayTemperature();
	
	std::cout << "Setting time & date" <<std::endl;
	rtc.setDate(10,37,19,15,2,22);
	rtc.displayTime();
	
	return 0;
}
