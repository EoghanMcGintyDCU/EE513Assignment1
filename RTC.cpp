#include <iostream>
#include<stdio.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<linux/i2c-dev.h>

#include "RTC.h"

#define BUFFER_SIZE 19      //0x00 to 0x12

RTC::RTC()
{}

RTC::~RTC()
{}

// the time is in the registers in encoded decimal form
int bcdToDec(char b) { return (b/16)*10 + (b%16); }

int readI2C(char* buf)
{
	int file;
	if((file=open("/dev/i2c-2", O_RDWR)) < 0){
	  	return -1;
	}
	if(ioctl(file, I2C_SLAVE, 0x68) < 0){
	  	return -1;
	}
	char writeBuffer[1] = {0x00};
	if(write(file, writeBuffer, 1)!=1){
		return -1;
	}
	if(read(file, buf, BUFFER_SIZE)!=BUFFER_SIZE){
		return -1;
	}
	close(file);
	return 0;
}

int RTC::displayTime()
{
	char buf[BUFFER_SIZE];
	readI2C(buf);
	printf("The RTC time is %02d:%02d:%02d\n", bcdToDec(buf[2]),
	     bcdToDec(buf[1]), bcdToDec(buf[0]));
	return 0;
}

int RTC::displayTemperature()
{
	char buf[BUFFER_SIZE];
	readI2C(buf);
	printf("The RTC temperature is %d\n", buf[17]);
	return 0;
}

int RTC::setDate()
{
	std::cout << "setDate" << std::endl;
	return 0;
}

int RTC::setAlarm()
{
	std::cout << "setAlarm" << std::endl;
	return 0;
}
