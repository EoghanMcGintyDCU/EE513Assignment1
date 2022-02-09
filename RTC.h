#include <fstream>

class RTC
{
private:

public:
	RTC();
	int displayTime();
	int displayTemperature();
	int setDate();
	int setAlarm();
	virtual ~RTC();
};
