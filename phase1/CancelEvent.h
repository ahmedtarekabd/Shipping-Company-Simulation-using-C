#pragma once

#include "Event.h"

class CancelEvent : public Event
{
public:
	CancelEvent(int id, Time time, Company* company);

	void Excute();

};

