#include <iostream>
#include <stdio.h> 
#include <fcntl.h> 
#include <sys/ioctl.h> 
#include <unistd.h> 
#include <linux/i2c-dev.h>

#include "RTC.h"

#define BUFFER_SIZE 19      //0x00 to 0x12
#define REG_TEMP_MSB 0x11
#define REG_TEMP_LSB 0x12

RTC::RTC()
{}

RTC::~RTC()
{}

// the time is in the registers in encoded decimal form
int bcdToDec(char b) { return (b/16)*10 + (b%16); }
char decToBcd(int i) { return (i/10)*16 + (i%10); } 

int readI2C(char* buf, size_t size)
{
	int file;
	if((file=open("/dev/i2c-2", O_RDONLY)) < 0){
	  	return -1;
	}
	if(ioctl(file, I2C_SLAVE, 0x68) < 0){
	  	return -1;
	}
	char writeBuffer[1] = {0x00};
	if(write(file, writeBuffer, 1) != 1){
		return -1;
	}
	if(read(file, buf, size)!=size){
		return -1;
	}
	close(file);
	return 0;
}

int writeI2C(char* buf, size_t size)
{
	int file;
	if((file=open("/dev/i2c-2", O_WRONLY)) < 0){
		return -1;
	}
	if(ioctl(file, I2C_SLAVE, 0x68) < 0){
		return -1;
	}
	if(write(file, buf, size)!=size){
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
	printf("The RTC temperature is %d.%02d Deg C\n", buf[REG_TEMP_MSB], buf[REG_TEMP_LSB]);
	return 0;
}

int RTC::setDate(int secs, int mins, int hours, int day, int month, int year)
{
	char buf[7];
	readI2C(buf);
	buf[0] = decToBcd(secs);
	buf[1] = decToBcd(mins);
	buf[2] = decToBcd(hours);
	buf[4] = decToBcd(day);
	buf[5] = decToBcd(month);
	buf[6] = decToBcd(year);
	writeI2C(buf, 7);
	std::cout << "Date Set" << std::endl;
	return 0;
}

int RTC::setAlarm()
{
	std::cout << "setAlarm" << std::endl;
	return 0;
}
