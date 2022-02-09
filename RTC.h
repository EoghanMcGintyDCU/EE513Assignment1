#include <fstream>

class RTC
{
private:

public:
	RTC();
	int displayTime();
	int displayTemperature();
	int setDate(int secs, int mins, int hours, int day, int date, int month, int year);
	int setAlarm();
	virtual ~RTC();
};
