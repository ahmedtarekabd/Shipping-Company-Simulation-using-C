#include "PromoteEvent.h"

PromoteEvent::PromoteEvent(int cargoID, Time time, int extramoney, Company* company) :Event(cargoID, time, company)
{
	ExtraMoney = extramoney;
}

void PromoteEvent::Excute()
{
	Cargos* cargo = nullptr;

	company->removeNormalCargo(cargo, cargoID);

	//checking the cargo found or not
	if (!cargo)
		return;

	//adding the extra cost change type the add the cargo to the vip list
	cargo->addCost(ExtraMoney);

	cargo->setCargoType(VIP);

	company->addVipCargo(cargo);

}

PromoteEvent::~PromoteEvent()
{



}