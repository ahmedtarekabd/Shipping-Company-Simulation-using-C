#pragma once
#include "PreparationEvent.h"
#include "Event.h"
#include "Time.h"
#include"Cargos.h"

PreparationEvent::PreparationEvent(Type TYP, Time ET, int ID, int DIST, int LT, int cost, Company* company)
	:Event(ID, ET, company)
{

   //intizailzing datamembers

	cargoType = TYP;
	DeliveryDistance = DIST;
	LoadTime = LT;
	Cost = cost;

}

//data from constructor of preparation time

void PreparationEvent::Excute()
{
	Cargos* NewCargo;

	//creating new cargo according to the type
	//adding each cargo to the required list

	switch (cargoType)
	{
	case VIP:
		NewCargo = new Cargos(EventTime,LoadTime,DeliveryDistance,Cost,cargoID,VIP);
		company->addVipCargo(NewCargo);
		break;

	case SPECIAL:
		NewCargo = new Cargos(EventTime,LoadTime,DeliveryDistance,Cost,cargoID,SPECIAL);
		company->addSpecialCargo(NewCargo);
		break;

	case NORMAL:
		NewCargo = new Cargos(EventTime,LoadTime,DeliveryDistance,Cost,cargoID,NORMAL);
		company->addNormalCargo(NewCargo);
		break;
	}
}

PreparationEvent::~PreparationEvent()
{



}
