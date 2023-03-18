#pragma once

#include "Time.h"
#include"Company.h"


class Event
{

	bool setId(int num);

	void setEventTime(int day, int hour); 

protected:
	
	int cargoID;

	Time EventTime;

	Company* company;

public:

	Event(int id, Time time, Company* Company); 

	int GetId() const;

	Time getEventTime() const;

	virtual void Excute() = 0;

	~Event();








};

