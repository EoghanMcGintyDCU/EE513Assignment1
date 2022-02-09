#include <fstream>

class RTC
{
private:
public:
	RTC();
	int displayTime();
	int displayDate();
	int displayTemperature();
	int setDate(int secs, int mins, int hours, int day, int date, int month, int year);
	int setAlarm1(int secs, int mins, int hours);
	int setAlarm2(int secs, int mins, int hours, int day, int date);
	virtual ~RTC();
};
