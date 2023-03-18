#include "Time.h"
#include <iostream>

using namespace std;

Time::Time()
{

	day = 0;
	hour = 0;

}

Time::Time(float hours)
{

	day = 0;

	while (hours >= 24)
	{

		incrementDay();
		hours -= 24;

	}

	// Remaining hours
	hour = hours;

}

Time::Time(int day, float hours)
{

	setDay(day);
	setHour(hours);

}

void Time::setDay(int d)
{

	if (d < 0)
		return;

	day = d;

}

void Time::incrementDay()
{

	setDay(day + 1);

}

void Time::setHour(float h)
{

	if (h < 0)
	{
		h = 0;
		return;
	}

	while (h >= 24)
	{

		incrementDay();
		h -= 24;

	}

	hour = h;

}

void Time::incrementHour()
{

	// reset hour
	if (hour + 1 >= 24)
	{

		incrementDay();
		setHour(0);

	}
	else
		setHour(hour + 1);

}

int Time::getDay() const
{

	return day;

}

int Time::getHour() const
{

	return hour;

}

int Time::timeInHours() const
{

	return (day * 24) + hour;

}

bool Time::operator ==(const Time& other)
{

	if (day == other.day && hour == other.hour)
		return true;

	return false;

}

bool Time::operator >(const Time& other)
{

	if (day > other.day || (day == other.day && hour > other.hour))
		return true;

	return false;

}

bool Time::operator >=(const Time& other)
{

	if (*this == other || *this > other)
		return true;

	return false;

}

bool Time::operator <(const Time& other)
{

	if (day < other.day || (day == other.day && hour < other.hour))
		return true;

	return false;

}

bool Time::operator <=(const Time& other)
{

	if (*this == other || *this < other)
		return true;

	return false;

}

Time Time::operator +(const Time& other)
{

	Time tmp;
	tmp.setDay(day + other.day);
	tmp.setHour(hour + other.hour);
	return tmp;

}

Time Time::operator -(const Time& other)
{
	
	Time tmp(0);

	tmp.setHour((day - other.day) * 24 + hour - other.hour);
	
	//tmp.setDay(day - other.day);
	//tmp.setHour((tmp.day * 24 + hour) - other.hour);
	return tmp;

}

void Time::print(bool newLine)
{

	cout << day << ":" << hour;

	if (newLine)
		cout << endl;

}

Time::~Time()
{

}
