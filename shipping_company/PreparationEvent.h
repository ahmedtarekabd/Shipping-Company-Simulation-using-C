#pragma once
#include "Event.h"
#include "Time.h"
#include"Cargos.h"

class PreparationEvent : public Event
{
     //data members

	Type cargoType;
	int DeliveryDistance;
	int LoadTime;
	int Cost;

public:

	PreparationEvent(Type TYP, Time ET, int ID, int DIST, int LT, int cost, Company* company);

	void Excute();

	~PreparationEvent();

};

