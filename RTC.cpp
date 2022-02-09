#include <iostream>
#include <stdio.h> 
#include <fcntl.h> 
#include <sys/ioctl.h> 
#include <unistd.h> 
#include <linux/i2c-dev.h>

#include "RTC.h"

#define BUFFER_SIZE 	19      //0x00 to 0x12
#define REG_0		0x00
#define REG_TEMP_MSB 	0x11
#define REG_TEMP_LSB 	0x12

RTC::RTC(){}

RTC::~RTC(){}

// the time is in the registers in encoded decimal form
int bcdToDec(char b) { return (b/16)*10 + (b%16); }
char decToBcd(int i) { return (i/10)*16 + (i%10); } 

int readI2C(char reg_addr, char* buf, size_t size){
	int file;
	if((file=open("/dev/i2c-2", O_RDWR)) < 0){
	  	return -1;
	}
	if(ioctl(file, I2C_SLAVE, 0x68) < 0){
	  	return -1;
	}
	char addrBuffer[1] = {reg_addr};
	if(write(file, addrBuffer, 1) != 1){
		return -1;
	}
	if(read(file, buf, size)!=size){
		return -1;
	}
	close(file);
	return 0;
}

// First byte in buf must be address writing to
int writeI2C(char* buf, size_t size){
	int file;
	if((file=open("/dev/i2c-2", O_RDWR)) < 0){
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

int RTC::displayTime(){
	char buf[BUFFER_SIZE];
	if(readI2C(REG_0, buf, BUFFER_SIZE)<0){
		std::cerr << "read failed" << std::endl;
		return -1;
	}

	printf("The RTC time is %02d:%02d:%02d\n", bcdToDec(buf[2]),
	     bcdToDec(buf[1]), bcdToDec(buf[0]));
	return 0;
}

int RTC::displayDate(){
	char buf[BUFFER_SIZE];
	if(readI2C(REG_0, buf, BUFFER_SIZE)<0){
		std::cerr<< "read failed" << std::endl;
		return -1;
	}
	printf("The RTC date is %02d/%02d/%02d\n", bcdToDec(buf[4]),
		bcdToDec(buf[5]), bcdToDec(buf[6]));
	return 0;
}

int RTC::displayTemperature(){
	char buf[BUFFER_SIZE];
	if(readI2C(REG_0, buf, BUFFER_SIZE)<0){
		std::cerr << "read failed" << std::endl;
		return -1;
	}
	printf("The RTC temperature is %d.%02d Deg C\n", buf[REG_TEMP_MSB], buf[REG_TEMP_LSB]);
	return 0;
}

int RTC::setDate(int secs, int mins, int hours, int day, int date, int month, int year){
	char buf[8];
	buf[1] = decToBcd(secs);
	buf[2] = decToBcd(mins);
	buf[3] = decToBcd(hours);
	buf[4] = decToBcd(day);
	buf[5] = decToBcd(date);
	buf[6] = decToBcd(month);
	buf[7] = decToBcd(year);
	
	buf[0] = REG_0;

	if(writeI2C(buf, 8) < 0){
		std::cerr << "write failed" << std::endl;
		return -1;
	}
	
	std::cout << "Date Set" << std::endl;
	return 0;
}

int RTC::setAlarm1(int secs, int mins, int hours){
	std::cout << "setAlarm1" << std::endl;
	return 0;
}

int RTC::setAlarm2(int secs, int mins, int hours, int day, int date){
	std::cout << "setAlarm2" <<std::endl;
	return 0;
}

