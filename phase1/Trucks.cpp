#include "Trucks.h"

// initialize number of trucks
int Trucks::numberOfNTrucks = 0;
int Trucks::numberOfSTrucks = 0;
int Trucks::numberOfVTrucks = 0;

Trucks::Trucks(int mt, int tc, int s, int jbc, int id, Type t)
{

	truckType = t;
	truckCapacity = tc;
	speed = s;
	JourneysBeforeCheckup = jbc;
	ID = id;

	totalNumOfCargos = 0;
	numOfJourneys = 0;
	totalNumOfJourneys = 0;

	cargos = new PriorityQueue<Cargos*, Time>;
	loadTime = new Time(0);
	movingTime = new Time(0);
	checkupDuration = new Time(mt);
	deliveryInterval = new Time(0);

}

// Setters
void Trucks::setTruckType(Type t)
{
	truckType = t;
}

void Trucks::setTruckCapacity(int tc)
{
	truckCapacity = tc;
}

void Trucks::setSpeed(int s)
{
	speed = s;
}

void Trucks::setJourneysBeforeCheckup(int jbc)
{
	JourneysBeforeCheckup = jbc;
}

void Trucks::setMovingTime(Time* time)
{

	*movingTime = *time + *loadTime;

}

void Trucks::incNumOfJourneys()
{
	numOfJourneys++;
	totalNumOfJourneys++;
}

void Trucks::setNumberOfJourneys(int numOfJour)
{
	numOfJourneys = numOfJour;
}

void Trucks::incremnetNumOfCargos()
{

	totalNumOfCargos++;

}

float Trucks::calcUtilization(Time* simTime)
{
	float utilization;

	if (totalNumOfJourneys == 0)
		return 0;

	utilization = ((float) totalNumOfCargos / (truckCapacity * totalNumOfJourneys)) * ((float) getTruckActiveTime().timeInHours() / (*simTime).timeInHours());

	return utilization;
}

void Trucks::setLoadTime(Time time)
{

	*loadTime = time;

}

// Getters
Type Trucks::getTruckType()
{
	return truckType;
}

Type Trucks::getCargosType()
{
	return cargosType;
}

int Trucks::getTruckCapacity()
{
	return truckCapacity;
}

int Trucks::getSpeed()
{
	return speed;
}

void Trucks::calcDeliveryInterval()
{
	//DI = (Delivery Distance of furthest cargo)/truck speed + Sum of unload times of all its cargos + time to come back

	int furthestDistance = 0;
	LinkedQueue<Cargos*> tempCargo;
	Cargos* cargo = nullptr;

	while (cargos->dequeue(cargo))
	{
		// Get Delivery Distance of Furthest Cargo
		if (furthestDistance < cargo->getDeliveryDistance())
		{
			furthestDistance = cargo->getDeliveryDistance();
		}

		tempCargo.enqueue(cargo);
	}

	// add cargos back to truck
	while (tempCargo.dequeue(cargo)) cargos->enqueue(cargo, *cargo->getDeliveryTime());

	// 2*(Delivery Distance of furthest cargo)/truck speed 
	// as time to come back = (Delivery Distance of furthest cargo)/truck speed 
	*deliveryInterval = *loadTime + 2 * ((float)furthestDistance / getSpeed());
	// Casting furthest distance prevents from truncating floating numbers

	truckActiveTime = *loadTime + *loadTime + ((float)furthestDistance / getSpeed());


}

int Trucks::getJourneysBeforeCheckup()
{
	return JourneysBeforeCheckup;
}

int Trucks::getId()
{
	return ID;
}

int Trucks::getNumberOfJourneys()
{
	return numOfJourneys;
}

int Trucks::getTotalNumberOfJourneys()
{
	return totalNumOfJourneys;
}

Time* Trucks::getLoadTime()
{
	return loadTime;
}

Time* Trucks::getMovingTime()
{
	return movingTime;
}

Time* Trucks::getCheckupDuration()
{
	return checkupDuration;
}

Time* Trucks::getDeliveryInterval()
{
	return deliveryInterval;
}

Time Trucks::getTruckActiveTime()
{

	return truckActiveTime;
}

void Trucks::incrementNumberOfTrucks(Type type)
{
	switch (type)
	{
	case NORMAL:
		numberOfNTrucks++;
		break;

	case SPECIAL:
		numberOfSTrucks++;
		break;

	case VIP:
		numberOfVTrucks++;
		break;
	}
}

void Trucks::decrementNumberOfTrucks(Type type)
{
	switch (type)
	{
	case NORMAL:
		numberOfNTrucks--;

	case SPECIAL:
		numberOfSTrucks--;

	case VIP:
		numberOfVTrucks--;
	}
}

int Trucks::getNumberOfTrucks(Type type)
{
	switch (type)
	{
	case NORMAL:
		return numberOfNTrucks;

	case SPECIAL:
		return numberOfSTrucks;

	case VIP:
		return numberOfVTrucks;
	}

}

int Trucks::getNumberofCargosInTruck()
{
	return cargos->getSize();
}

//PriorityQueue<Cargos*, Time>* Trucks::getCargosInTrucks()
//{
//	return cargos;
//}

int Trucks::getNumOfCargos()
{

	return totalNumOfCargos;

}


bool Trucks::addCargo(Cargos* c)
{

	// No cargo
	if (!c)
		return false;

	//Cargos* cargo = nullptr;
	//cargos->peek(cargo);

	if (cargos->getSize() < truckCapacity)
	{

		cargos->enqueue(c, *c->getDeliveryTime());
		*loadTime = *loadTime + c->getLoadUnloadTime();
		cargosType = c->getCargoType();

		return true;

	}

	return false;

}

bool Trucks::removeCargo(Cargos*& cargo)
{

	Cargos* temp = nullptr;
	if (cargos->dequeue(temp))
	{

		*loadTime = *loadTime - temp->getLoadUnloadTime();
		cargo = temp;
		return true;

	}

	return false;

}

void Trucks::printCargos()
{

	cargos->printQueue();

}

//int Trucks::totalLoadTime()
//{
//	Cargos* temp = nullptr;
//	int sum = 0;
//
//	for (int i = 0, z = cargos->getSize(); i < z; i++)
//	{
//		cargos->dequeue(temp);
//		sum += temp->getLoadUnloadTime();
//		cargos->enqueue(temp, temp->getDeliveryTime());
//	}
//	return sum;
//}

void Trucks::updateDeliveryTime()
{

	// 7[1(2), 2(3+2), 3]
	// first destination(50m) --------- second destination(100m) --------- third destination(150m)
	Cargos* cargo = nullptr;
	LinkedQueue<Cargos*> tmp;
	Time totalTime(0);


	if (cargos->dequeue(cargo))
	{
		tmp.enqueue(cargo);
		totalTime = cargo->getLoadUnloadTime();
	}

	for (int i = 0, n = cargos->getSize(); i < n; i++)
	{

		cargos->dequeue(cargo);
		tmp.enqueue(cargo);

		cargo->updateDeliveryTime(&totalTime);

		totalTime = totalTime + cargo->getLoadUnloadTime();

	}

	while (tmp.dequeue(cargo))
		cargos->enqueue(cargo, *cargo->getDeliveryTime());

}

bool Trucks::operator==(const Trucks& other)
{

	if (ID == other.ID) return true;

	return false;

}

Trucks::~Trucks()
{
	delete cargos;
}