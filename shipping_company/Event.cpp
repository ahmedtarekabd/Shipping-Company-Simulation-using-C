#include "Event.h"
#include "Time.h"
#include "Company.h"
#include <iostream>

using namespace std;

//constrnctor

Event::Event(int id, Time time, Company* Company)
{
	setId(id);
	setEventTime(time.getDay(),time.getHour());
	company = Company;
}

//setters

bool Event::setId(int x)
{
	if (x <= 0)
		return false;

	cargoID = x;
	return true;

}

void Event::setEventTime(int day, int hour)
{
	EventTime.setDay(day);
	EventTime.setHour(hour);
}

//getters

int Event::GetId() const
{
	return cargoID;

}


Time Event::getEventTime() const
{
	return EventTime;
}


Event::~Event()
{



}
