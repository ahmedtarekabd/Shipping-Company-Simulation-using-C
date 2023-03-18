#include "Cargos.h"
#include "Trucks.h"

Cargos::Cargos(int id)
{
	ID = id;
	cargoType = NORMAL;
	loadUnloadTime = 0;
	deliveryDistance = 0;
	cost = 0;
	priority = 0;
	truck = nullptr;

	prevUnloadTimes = new Time(0);

	calcPriority();
}

Cargos::Cargos(Time pt, int lt, int dd, int c, int id, Type t)
{
	cargoType = t;
	preparationTime = pt;
	loadUnloadTime = lt;
	deliveryDistance = dd;
	cost = c;
	ID = id;
	priority = 0;
	truck = nullptr;

	prevUnloadTimes = new Time(0);
	deliveryTime = new Time(0);

	calcPriority();
}

void Cargos::setCargoType(Type type)
{
	cargoType = type;
}

void Cargos::setPreparationTime(Time pt)
{
	preparationTime = pt;
}

void Cargos::setLoadUnloadTime(int lt)
{
	loadUnloadTime = lt;

}

void Cargos::setDeliveryDistance(int dd)
{
	deliveryDistance = dd;
}

void Cargos::setCost(int c)
{
	cost = c;
}

void Cargos::setId(int id)
{
	ID = id;
}

void Cargos::setIsAutoP(bool ap)
{
	isAutoP = ap;
}

void Cargos::setIsMaxW(bool mw)
{
	isMaxW = mw;
}

void Cargos::setTruck(Trucks* t)
{

	truck = t;

}

Type Cargos::getCargoType()
{
	return cargoType;
}

Time Cargos::getPreparationTime()
{
	return preparationTime;
}

int Cargos::getLoadUnloadTime()
{
	return loadUnloadTime;
}

int Cargos::getDeliveryDistance()
{
	return deliveryDistance;
}

int Cargos::getCost()
{
	return cost;
}

int Cargos::getId()
{
	return ID;
}

//int Cargos::GetMaxW()
//{
//	return Max
//}

void Cargos::addCost(int extraMoney)
{

	cost = cost + extraMoney;
	calcPriority();
}

bool Cargos::IsAutoP()
{
	return isAutoP;
}

bool Cargos::IsMaxW()
{
	return isMaxW;
}

int Cargos::getTruckId()
{

	return truck->getId();

}

Time* Cargos::getMovingTime()
{

	return truck->getMovingTime();

}

Time Cargos::getWaitingTime()
{
	return *getMovingTime() - getPreparationTime();
}

bool Cargos::operator==(const Cargos& other)
{

	if (ID == other.ID) return true;

	return false;
}

void Cargos::calcPriority()
{
	int pt = 0;
	int dd = 0;
	int  Cost = 0;

	if (loadUnloadTime > 0 && loadUnloadTime <= 2)
		pt = 1;
	else if (loadUnloadTime > 2 && loadUnloadTime <= 5)
		pt = 2;
	else if (loadUnloadTime > 5)
		pt = 3;

	if (deliveryDistance > 0 && deliveryDistance <= 50)
		dd = 1;
	else if (deliveryDistance > 50 && deliveryDistance <= 250)
		dd = 2;
	else if (deliveryDistance > 250)
		dd = 3;

	if (cost > 0 && cost <= 50)
		Cost = 4;
	else if (cost > 50 && cost <= 250)
		Cost = 3;
	else if (cost > 250 && cost <= 500)
		Cost = 2;
	else if (cost > 500 && cost <= 1000)
		Cost = 1;
	else if (cost > 1000)
		Cost = 0;

	priority = pt + dd + Cost;
}

void Cargos::calcDeliveryTime()
{

	// 90/140 = 0.6	
	// 6, 4
	// (2 + 0.5) (3 + 1 + 2)
	// don't change the distance because it is already calculated
	*deliveryTime = *truck->getMovingTime() + ((float)deliveryDistance / truck->getSpeed()) + loadUnloadTime + *prevUnloadTimes;
	// (1 + 2) (1 + 3 + 2)
	

}

Time* Cargos::getDeliveryTime()
{

	calcDeliveryTime();
	return deliveryTime;

}

void Cargos::updateDeliveryTime(Time* time)
{

	*prevUnloadTimes = *time;
	calcDeliveryTime();

}

int Cargos::getPriority()
{
	return priority;
}