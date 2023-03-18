#pragma once

#include "Event.h"

class PromoteEvent : public Event
{

	int ExtraMoney;
	// takes time from event, and takes CargoId from events bardo

public:

	//constructor
	PromoteEvent(int cargoID, Time time, int extramoney, Company* Company);

	//Excute
	void Excute();

	~PromoteEvent();

};

