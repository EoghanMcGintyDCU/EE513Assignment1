#include <fstream>

enum class Freq
{
	freq1 = 0b00,
	freq2 = 0b01,
	freq3 = 0b10,
	freq4 = 0b11
};

class RTC
{
public:
	RTC();
	int displayTime();
	int displayDate();
	int displayTemperature();
	int setDate(int secs, int mins, int hours, int day, int date, int month, int year);
	int setAlarm1(int secs, int mins, int hours);
	int setAlarm2(int mins, int hours, int day);
	int readAlarm1();
	int readAlarm2();
	int alarmTest();
	int setSquareWave(Freq freq);
	virtual ~RTC();
};
