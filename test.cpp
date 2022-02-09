#include <iostream>
#include "RTC.h"

int main()
{
	RTC rtc;
	std::cout << "Reading current time" << std::endl;
	rtc.displayTime();
	std::cout << "Reading current temperature" << std::endl;
	rtc.displayTemperature();

	return 0;
}
