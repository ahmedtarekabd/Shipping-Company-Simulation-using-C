#pragma once

#include "CancelEvent.h"
#include "Event.h"
#include "Time.h"
#include "Cargos.h"
#include "Company.h"
#include <iostream>

CancelEvent::CancelEvent(int cargoId, Time time, Company* company)
	:Event(cargoId, time, company)
{

}

void CancelEvent::Excute()
{ 

	Cargos* cargo = nullptr;

	//to grt the cargo to be deleted
	company->removeNormalCargo(cargo, cargoID);

	delete cargo;

}

