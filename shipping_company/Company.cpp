#include "Company.h"
#include "Event.h"
#include "PreparationEvent.h"
#include "PromoteEvent.h"
#include "CancelEvent.h"
#include "Enums.h"

#include <string>

Company::Company()
{

	currentTime = new Time;

	autoP = 0;
	maxWait = 0;
	totalActiveTime = 0;

	// allocate new list for each list
	events = new LinkedQueue<Event*>;

	//currentTime = new Time;
	normalTrucks = new LinkedQueue<Trucks*>;
	specialTrucks = new LinkedQueue<Trucks*>;
	vipTrucks = new LinkedQueue<Trucks*>;
	loadingTrucks = new LinkedQueue<Trucks*>;
	inCheckupNormalTrucks = new LinkedQueue<Trucks*>;
	inCheckupSpecialTrucks = new LinkedQueue<Trucks*>;
	inCheckupVipTrucks = new LinkedQueue<Trucks*>;
	movingTrucks = new PriorityQueue<Trucks*, Time>;

	normalCargos = new LinkedList<Cargos*>;
	specialCargos = new LinkedQueue<Cargos*>;
	vipCargos = new PriorityQueue<Cargos*, int>;
	deliveredCargos = new LinkedQueue<Cargos*>;


	// for UI
	userInterface = new UI(this);
}

// ========== Files ==========
bool Company::ReadFile(string fileName)
{
	//Read Trucks info

	ifstream inputFile(fileName);

	if (inputFile.is_open())
	{
		// read file
		inputFile >> N >> S >> V;
		inputFile >> NS >> SS >> VS;
		inputFile >> NTC >> STC >> VTC;
		inputFile >> J >> CN >> CS >> CV;
		inputFile >> AutoP >> MaxW;

		// create trucks
		Trucks* truckptr;


		// Creating Normal trucks
		for (int i = 0; i < N; i++)
		{
			// increment number of normal trucks
			Trucks::incrementNumberOfTrucks(NORMAL);
			int id = Trucks::getNumberOfTrucks(NORMAL);

			truckptr = new Trucks(CN, NTC, NS, J, id, NORMAL);
			// Add this truck to truck list
			addNormalTruck(truckptr);
		}

		// Creating Special trucks
		for (int i = 0; i < S; i++)
		{

			// increment number of Special trucks
			Trucks::incrementNumberOfTrucks(SPECIAL);
			int id = Trucks::getNumberOfTrucks(SPECIAL);

			truckptr = new Trucks(CS, STC, SS, J, id, SPECIAL);
			// Add this truck to truck list
			addSpecialTruck(truckptr);
		}

		// Creating VIP trucks
		for (int i = 0; i < V; i++)
		{
			// increment number of Vip trucks
			Trucks::incrementNumberOfTrucks(VIP);
			int id = Trucks::getNumberOfTrucks(VIP);


			truckptr = new Trucks(CV, VTC, VS, J, id, VIP);
			// Add this truck to truck list
			addVipTruck(truckptr);
		}

		// AutoP & MaxW
		autoP = AutoP;
		maxWait = MaxW;

		// Trucks info
		normalTrucksInfo[SPEED] = NS;
		normalTrucksInfo[CAPACITY] = NTC;
		normalTrucksInfo[CHECKUP_JUOURNEY] = J;
		normalTrucksInfo[CHECKUP_DURATION] = CN;

		specialTrucksInfo[SPEED] = SS;
		specialTrucksInfo[CAPACITY] = STC;
		specialTrucksInfo[CHECKUP_JUOURNEY] = J;
		specialTrucksInfo[CHECKUP_DURATION] = CS;

		vipTrucksInfo[SPEED] = VS;
		vipTrucksInfo[CAPACITY] = VTC;
		vipTrucksInfo[CHECKUP_JUOURNEY] = J;
		vipTrucksInfo[CHECKUP_DURATION] = VS;


		// Read events info

		inputFile >> NumOfEvents;

		// Create events
		Event* eventptr = nullptr;

		for (int i = 0; i < NumOfEvents; i++)
		{
			inputFile >> eventType;

			switch (eventType)
			{
				//Ready Event

			case 'R':
				// Read line
				inputFile >> TYPChar >> day >> doubleDot >> hour >> ID >> DIST >> LT >> Cost;

				ET.setDay(day);
				ET.setHour(hour);
				TYP = getType(TYPChar);
				//set cargotime 

				// create event pointer with these values as a constructor
				eventptr = new PreparationEvent(TYP, ET, ID, DIST, LT, Cost, this);

				// Add the event to ReadyList
				addEvent(eventptr);				

				break;

				//Cancelation Event

			case 'X':
				// Read line
				inputFile >> day >> doubleDot >> hour >> ID;

				ET.setDay(day);
				ET.setHour(hour);

				// create event pointer with these values as a constructor
				eventptr = new CancelEvent(ID, ET, this);

				//Add the event to CancelationList
				addEvent(eventptr);

				break;

				//Promotion Event
			case 'P':
				// Read line
				inputFile >> day >> doubleDot >> hour >> ID >> ExtraMoney;

				ET.setDay(day);
				ET.setHour(hour);

				// create event pointer with these values as a constructor
				eventptr = new PromoteEvent(ID, ET, ExtraMoney, this); //error ??

				//Add the event to PromotionList
				addEvent(eventptr);

				break;
			}
		}
		return true;
		// close file
		inputFile.close();

	}
	else
		return false;		// couldn't read the file/not found

}

void Company::WriteFile()
{

	ofstream outputFile;
	outputFile.open("outputFile.txt", ios::out);

	Cargos* cargo = nullptr;

	// cargos size
	int cargosSize = deliveredCargos->getSize(); // number of all cargos

	// counten autopromotionr i
	float percentage = (numAutoPromoted / numNormalCargos + numAutoPromoted) * 100;
	// number of autopromoted cargos

	// Average waitinng time of cargos
	Time AvgWaitTime;
	AvgWaitTime.setHour(getTotalWaitingTime() / cargosSize);

	// Average Active time
	float AvgActiveTime = 0;
	AvgActiveTime = avgPercentageActiveTime() * 100;

	float AvgUtilizationTime = 0;
	AvgUtilizationTime = getTotalUtilizationTime() * 100;


	if (outputFile.is_open())
	{
		outputFile << "CDT		ID		PT		WT		TID" << endl;

		// loop
		for (int i = 0, z = deliveredCargos->getSize(); i < z; i++)
		{
			deliveredCargos->dequeue(cargo);

			// Cargos Data
			outputFile << cargo->getDeliveryTime()->getDay() << ":" << cargo->getDeliveryTime()->getHour() << "		"
				<< cargo->getId() << "		"
				<< cargo->getPreparationTime().getDay() << ":" << cargo->getPreparationTime().getHour() << "		"
				<< cargo->getWaitingTime().getDay() << ":" << cargo->getWaitingTime().getHour() << "		"
				<< cargo->getTruckId() << endl;

			deliveredCargos->enqueue(cargo);
		}

		// Split
		outputFile << "----------------------------------------------" << endl;

		// Total number of cargos
		outputFile << "Cargos: " << (cargosSize) << " [N: " << numNormalCargos << ", S: " << numSpecialCargos << ", V: " << numVipCargos << "]" << endl;

		// Average wait time
		//total wait time / num of cargos
		outputFile << "Cargo Avg Wait = " << AvgWaitTime.getDay() << ":" << AvgWaitTime.getHour() << endl;

		// Promoted Cargos
		outputFile << "Auto-Promoted Cargos: " << percentage << "%" << endl;

		// Total number of Trucks
		outputFile << "Trucks: " << (N + V + S) << " [N: " << N << ", S: " << S << ", V: " << V << "]" << endl;

		// Average active time
		outputFile << "Avg Active time = " << AvgActiveTime << "%" << endl;

		// Average utilization
		outputFile << "Avg utilization time = " << AvgUtilizationTime << "%" << endl;

		outputFile.close();

	}

}

Time* Company::getCurrentTime()
{
	return currentTime;
}



// ========== Adding ==========

void Company::addEvent(Event* event)
{

	events->enqueue(event);

}

void Company::addNormalTruck(Trucks* truck)
{

	normalTrucks->enqueue(truck);

}

void Company::addSpecialTruck(Trucks* truck)
{

	specialTrucks->enqueue(truck);

}

void Company::addVipTruck(Trucks* truck)
{

	vipTrucks->enqueue(truck);

}

void Company::addLoadingTruck(Trucks* truck)
{

	loadingTrucks->enqueue(truck);

}

void Company::addCheckupNormalTruck(Trucks* truck)
{

	inCheckupNormalTrucks->enqueue(truck);

}

void Company::addCheckupSpecialTruck(Trucks* truck)
{

	inCheckupSpecialTrucks->enqueue(truck);

}

void Company::addCheckupVipTruck(Trucks* truck)
{

	inCheckupVipTrucks->enqueue(truck);

}

void Company::addMovingTrucks(Trucks* truck)
{

	// missing truck priority

	Cargos* cargo = nullptr;

	if (truck->removeCargo(cargo))
	{

		truck->addCargo(cargo);
		movingTrucks->enqueue(truck, *cargo->getDeliveryTime());

	}
	// truck empty but still moving (returning back to the company)
	else
		// let the priority be the finish time
		movingTrucks->enqueue(truck, *truck->getDeliveryInterval() + *truck->getMovingTime());

}


// Cargos
void Company::addNormalCargo(Cargos* cargo)
{

	normalCargos->InsertEnd(cargo);

}

void Company::addSpecialCargo(Cargos* cargo)
{


	specialCargos->enqueue(cargo);

}

void Company::addDeliveredCargo(Cargos* cargo)
{

	deliveredCargos->enqueue(cargo);

}

void Company::addVipCargo(Cargos* cargo)
{

	vipCargos->enqueue(cargo, cargo->getPriority());

}


// ========== Removing ==========

bool Company::removeEvent()
{

	Event* removed;
	events->dequeue(removed);

	if (removed == nullptr)
		return false;

	return true;
}

// Trucks
bool Company::removeNormalTruck(Trucks*& truck)
{

	normalTrucks->dequeue(truck);
	if (truck == nullptr)
		return false;
	return true;

}

bool Company::removeSpecialTruck(Trucks*& truck)
{

	specialTrucks->dequeue(truck);
	if (truck == nullptr)
		return false;
	return true;

}

bool Company::removeVipTruck(Trucks*& truck)
{

	vipTrucks->dequeue(truck);
	if (truck == nullptr)
		return false;
	return true;

}

bool Company::removeLoadingTruck(Trucks*& truck)
{

	loadingTrucks->dequeue(truck);
	if (truck == nullptr)
		return false;
	return true;

}

bool Company::removeInCheckupNormalTruck(Trucks*& truck)
{

	inCheckupNormalTrucks->dequeue(truck);
	if (truck == nullptr)
		return false;
	return true;

}

bool Company::removeInCheckupSpecialtrucks(Trucks*& truck)
{

	inCheckupSpecialTrucks->dequeue(truck);
	if (truck == nullptr)
		return false;
	return true;

}

bool Company::removeInCheckupViptrucks(Trucks*& truck)
{

	inCheckupVipTrucks->dequeue(truck);
	if (truck == nullptr)
		return false;
	return true;

}

bool Company::removeMovingTruck(Trucks*& truck, int id)
{

	Trucks* targetCargo = nullptr;
	Trucks* temp = nullptr;

	for (int i = 0, n = movingTrucks->getSize(); i < n; i++)
	{

		movingTrucks->dequeue(temp);
		if (temp->getId() == id)
			targetCargo = temp;
		// else
			// priority el truck
			// movingTrucks->enqueue(temp);

	}

	// truck not found
	if (targetCargo == nullptr)
	{

		truck = nullptr;
		return false;

	}

	// truck found
	truck = targetCargo;
	targetCargo = nullptr;
	return true;

}

// Cargos
bool Company::removeNormalCargo(Cargos*& cargo, int id)
{

	cargo = normalCargos->Find(id);
	normalCargos->DeleteNode(cargo);
	if (cargo == nullptr)
		return false;
	return true;

}

bool Company::removeNormalCargoBeg(Cargos*& cargo)
{

	normalCargos->DeleteFirst(cargo);
	if (cargo == nullptr)
		return false;
	return true;

}

bool Company::removeSpecialCargo(Cargos*& cargo, int id)
{

	specialCargos->dequeue(cargo);
	if (cargo == nullptr)
		return false;
	return true;

}

bool Company::removeVipCargo(Cargos*& cargo, int id)
{

	vipCargos->dequeue(cargo);
	if (cargo == nullptr)
		return false;
	return true;

}

bool Company::removeDeliveredCargo(Cargos*& cargo, int id)
{

	deliveredCargos->dequeue(cargo);
	if (cargo == nullptr)
		return false;
	return true;

}

void Company::assignTrucks()
{

	// A truck can't be loaded with more than one cargo type in the same journey
	// y3ny fel assignment order lazem 
	// 


	// Max waiting rule
	// waiting normal cargos
	maxWNormalCargos();
	// waiting special cargos
	maxWSpecialCargos();

	// Get cargos needed to be assigned from each list (at the same time)
	// Vip
	assignVipCargo();

	// Special
	assignSpecialCargo();

	// Normal
	assignNormalCargo();

}


void Company::assignNormalCargo()
{

	Trucks* truck = nullptr;
	Cargos* cargo = nullptr;

	// Normal
	if (!normalTrucks->isEmpty())
	{

		// check capacity
		if (normalCargos->getSize() >= normalTrucksInfo[CAPACITY])
			if (approveLoadingTruck(NORMAL))
				if (removeVipTruck(truck))
				{
					// add it to loading trucks
					for (int i = 0; i < normalTrucksInfo[CAPACITY]; i++)
					{

						removeNormalCargoBeg(cargo);

						if (cargo)
						{

							// setTruck(truck)
							cargo->setTruck(truck);
							truck->addCargo(cargo);

						}

					}
					assignLoadingTruck(truck);

				}
	}
	else if (!vipTrucks->isEmpty())
	{

		// check capacity
		if (normalCargos->getSize() >= vipTrucksInfo[CAPACITY])
			if (approveLoadingTruck(NORMAL))
				if (removeVipTruck(truck))
				{
					// add it to loading trucks
					for (int i = 0; i < vipTrucksInfo[CAPACITY]; i++)
					{

						removeNormalCargoBeg(cargo);

						if (cargo)
						{

							// setTruck(truck)
							cargo->setTruck(truck);
							truck->addCargo(cargo);

						}

					}
					assignLoadingTruck(truck);

				}
	}

}

void Company::assignSpecialCargo()
{

	Trucks* truck = nullptr;
	Cargos* cargo = nullptr;

	if (!specialTrucks->isEmpty())
	{

		// check capacity
		if (specialCargos->getSize() >= specialTrucksInfo[CAPACITY])
			if (approveLoadingTruck(SPECIAL))
				if (removeSpecialTruck(truck))
				{
					// add it to loading trucks
					for (int i = 0; i < specialTrucksInfo[CAPACITY]; i++)
					{

						specialCargos->dequeue(cargo);

						if (cargo)
						{

							// setTruck(truck)
							cargo->setTruck(truck);
							truck->addCargo(cargo);

						}

					}
					assignLoadingTruck(truck);

				}
	}

}

void Company::assignVipCargo()
{

	Trucks* truck = nullptr;
	Cargos* cargo = nullptr;

	if (!vipTrucks->isEmpty())
	{

		// check capacity
		if (vipCargos->getSize() >= vipTrucksInfo[CAPACITY])
		{
			if (approveLoadingTruck(VIP))
				if (removeVipTruck(truck))
				{
					// add it to loading trucks
					for (int i = 0; i < vipTrucksInfo[CAPACITY]; i++)
					{

						vipCargos->dequeue(cargo);

						if (cargo)
						{

							// setTruck(truck)
							cargo->setTruck(truck);
							truck->addCargo(cargo);

						}

					}
					// add truck to appropriate list
					assignLoadingTruck(truck);

				}
		}
		else if (events->isEmpty() && vipCargos->getSize() == 1)
		{

			if (approveLoadingTruck(VIP))
				if (removeVipTruck(truck))
				{
					// add it to loading trucks
					vipCargos->dequeue(cargo);
					if (cargo)
					{

						// setTruck(truck)
						cargo->setTruck(truck);
						truck->addCargo(cargo);

					}
					// add truck to appropriate list
					assignLoadingTruck(truck);

				}

		}
	}
	else if (!normalTrucks->isEmpty())
	{

		// check capacity
		if (vipCargos->getSize() >= normalTrucksInfo[CAPACITY])
			if (approveLoadingTruck(VIP))
				if (removeNormalTruck(truck))
				{
					// add it to loading trucks
					for (int i = 0; i < normalTrucksInfo[CAPACITY]; i++)
					{

						vipCargos->dequeue(cargo);

						if (cargo)
						{

							// setTruck(truck)
							cargo->setTruck(truck);
							truck->addCargo(cargo);

						}

					}
					assignLoadingTruck(truck);

				}
	}
	else if (!specialTrucks->isEmpty())
	{

		// check capacity
		if (vipCargos->getSize() >= specialTrucksInfo[CAPACITY])
			if (approveLoadingTruck(VIP))
				if (removeSpecialTruck(truck))
				{
					// add it to loading trucks
					for (int i = 0; i < specialTrucksInfo[CAPACITY]; i++)
					{

						vipCargos->dequeue(cargo);

						if (cargo)
						{

							// setTruck(truck)
							cargo->setTruck(truck);
							truck->addCargo(cargo);

						}

					}
					assignLoadingTruck(truck);

				}
	}

}

void Company::assignLoadingTruck(Trucks* truck)
{

	loadingTrucks->enqueue(truck);
	// set moving time
	truck->setMovingTime(currentTime);

}

bool Company::approveLoadingTruck(Type type)
{

	// Approval should be based on types of cargos not 

	Trucks* tmp = nullptr;

	bool approve = true;

	for (int i = 0, z = loadingTrucks->getSize(); i < z; i++)
	{

		loadingTrucks->dequeue(tmp);
		loadingTrucks->enqueue(tmp);

		// Don't approve (adding it to loading)
		if (type == tmp->getCargosType())
			approve = false;

	}

	return approve;

}

void Company::assignLoadingCargo(Cargos* cargo)
{



}

void Company::assignMaintainanceCargo(Cargos* cargo)
{



}

void Company::maxWNormalCargos()

{

	Cargos* temp = nullptr;

	int size = normalCargos->getSize();


	int num = 0;
	//get number of cargos
	for (int i = 0; i < size; i++)
	{
		normalCargos->DeleteFirst(temp);
		if (*currentTime >= temp->getPreparationTime() + maxWait)
			num++;
		normalCargos->InsertEnd(temp);
	}

	//num of all cargos can be loaded now
	int numCargo = normalTrucks->getSize() * normalTrucksInfo[CAPACITY];
	Trucks* truck = nullptr;
	int counter = 0;

	// 34an a3rf h3ml while 3la anhi 3dd
	// ana 3aml while m3rf4 mkan el cargos 
	// fa b3ml while wi kol mla2i wahda b3ml minus
	bool firstTime = true;

	if (numCargo == 0)
	{
		int numvipcargos = vipTrucks->getSize() * vipTrucksInfo[CAPACITY];
		Trucks* truck = nullptr;
		int counter = 0;
		if (num > numvipcargos)
		{
			while (numvipcargos > 0)
			{
				vipCargos->dequeue(temp);
				if (*currentTime >= temp->getPreparationTime() + maxWait)
				{
					if (counter == vipTrucksInfo[CAPACITY])
					{
						vipTrucks->dequeue(truck);
						counter = 0;
						
						firstTime = true;

					}


					temp->setTruck(truck);
					truck->addCargo(temp);
					if (firstTime)
					{
						assignLoadingTruck(truck);
						firstTime = false;
					}
					numvipcargos--;
					counter++;
				}
				else
					vipCargos->enqueue(temp, temp->getPriority());
			}

		}
		else
		{
			while (num > 0)
			{
				vipCargos->dequeue(temp);
				if (*currentTime >= temp->getPreparationTime() + maxWait)
				{
					if (counter == vipTrucksInfo[CAPACITY] + 1 || counter == 0)
					{
						vipTrucks->dequeue(truck);
						counter = 0;

						firstTime = true;
					}


					temp->setTruck(truck);
					truck->addCargo(temp);
					if (firstTime)
					{
						assignLoadingTruck(truck);
						firstTime = false;
					}
					num--;
					counter++;
				}
				else
					vipCargos->enqueue(temp, temp->getPriority());
			}
		}
	}
	else
	{
		if (num > numCargo)
		{
			while (numCargo > 0)
			{
				normalCargos->DeleteFirst(temp);
				if (*currentTime >= temp->getPreparationTime() + maxWait)
				{
					if (counter == normalTrucksInfo[CAPACITY])
					{
						normalTrucks->dequeue(truck);
						counter = 0;
						firstTime = true;
					}


					temp->setTruck(truck);
					truck->addCargo(temp);
					if (firstTime)
					{
						assignLoadingTruck(truck);
						firstTime = false;
					}
					numCargo--;
					counter++;
				}
				else
					normalCargos->InsertEnd(temp);
			}

		}
		else
		{
			while (num > 0)
			{
				normalCargos->DeleteFirst(temp);
				if (*currentTime >= temp->getPreparationTime() + maxWait)
				{
					if (counter == normalTrucksInfo[CAPACITY] + 1 || counter == 0)
					{
						normalTrucks->dequeue(truck);
						counter = 0;
					}


					temp->setTruck(truck);
					truck->addCargo(temp);
					assignLoadingTruck(truck);
					num--;
					counter++;
				}
				else
					normalCargos->InsertEnd(temp);
			}
		}
	}
}


void Company::maxWSpecialCargos()
{

	Cargos* cargo = nullptr;
	Trucks* truck = nullptr;

	int numberOfCargos = 0;
	bool firstTime = true;

	while (specialCargos->peek(cargo))
	{

		if (*currentTime >= cargo->getPreparationTime() + Time(maxWait))
		{

			if (!specialTrucks->isEmpty())
			{

				if (numberOfCargos > specialTrucksInfo[CAPACITY])
				{
					numberOfCargos = 0;
				}
				if (numberOfCargos == 0)
				{
					removeSpecialTruck(truck);
					firstTime = true;
				}
				specialCargos->dequeue(cargo);
				if (cargo)
				{

					cargo->setTruck(truck);
					truck->addCargo(cargo);
					numberOfCargos++;

				}
				if (firstTime)
				{

					assignLoadingTruck(truck);
					firstTime = false;

				}

			}
			else
				break;

		}
		else
			break;

	}


}

void Company::changeType(Cargos* cargo, int cargoID, Type newtype)
{
	//change type
	cargo->setCargoType(newtype);
}

Type Company::getType(char type)
{
	switch (type) {
	case 'N':
		return NORMAL;
	case 'S':
		return SPECIAL;
	case 'V':
		return VIP;
	}
}

bool Company::inWorkingHours()
{

	return (currentTime->getHour() >= 5 && currentTime->getHour() <= 23);
	//return (*currentTime >= Time(currentTime, 5) && *currentTime <= 23)

}

// ========== Simulation ==========
void Company::simulatePhase1()
{

	// Phase 1 only 

	int numOfTimesteps = 0;
	string fileName;

	fileName = userInterface->startSimulation();
	ReadFile(fileName);
	userInterface->selectMode();

	// until all cargos are delivered
	// all lists are empty except delivered cargo list
	while (!events->isEmpty() || !normalCargos->getSize() == 0 || !specialCargos->isEmpty() || !vipCargos->isEmpty())
	{

		excuteEvents();

		// each 5 timesteps remove one cargo from
		// each list and add it to delivered
		if (numOfTimesteps == 5)
		{

			Cargos* temp = nullptr;

			removeNormalCargoBeg(temp);
			if (temp)
				deliveredCargos->enqueue(temp);
			temp = nullptr;

			specialCargos->dequeue(temp);
			if (temp)
				deliveredCargos->enqueue(temp);
			temp = nullptr;

			vipCargos->dequeue(temp);
			if (temp)
				deliveredCargos->enqueue(temp);
			temp = nullptr;

			numOfTimesteps = 0;

		}


		userInterface->simulateMode();

		currentTime->incrementHour();
		numOfTimesteps++;

	}

	userInterface->endSimulation();

}

void Company::simulate()
{

	string fileName;
	bool readFile = false;
	int count = 0;

	do
	{

		// Max 5 attempts
		if (count == 5)
		{

			userInterface->wronginput();
			return;

		}

		fileName = userInterface->startSimulation();
		readFile = ReadFile(fileName);
		count++;
	} while (!readFile);

	// consider adding the counter to this selection also
	userInterface->selectMode();

	// until all cargos are delivered
	// all lists are empty except delivered cargo list
	while (simulationEnds())
	{

		// Add cargos to its waiting lists
		excuteEvents();
		// assign needed cargos to trucks if there
		if (inWorkingHours())
			assignTrucks();

		truckLoadToMove();
		truckMoveToAvailOrCheck();
		truckCheckToAvail();
		autoPromotion();

		userInterface->simulateMode();
		currentTime->incrementHour();

	}

	WriteFile();
	userInterface->endSimulation();

}

void Company::excuteEvents()
{
	Event* tmpEvent;

	while (true)
		if (events->peek(tmpEvent)) // see first event in Queue 
		{
			if (tmpEvent->getEventTime() == *currentTime) // check if event time = current time 
			{
				events->dequeue(tmpEvent);
				tmpEvent->Excute(); // excute event
			}
			else
				break;
		}
		else
			break;

}

bool Company::simulationEnds()
{

	// Need to add the remaining lists (except delivered)
	return !events->isEmpty() || !normalCargos->getSize() == 0 || !specialCargos->isEmpty() || !vipCargos->isEmpty() || !loadingTrucks->isEmpty() || !movingTrucks->isEmpty();

}

// ========== Print Lists ==========
void Company::printEmptyTrucks()
{
	// get total size
	int totalSize = normalTrucks->getSize() + specialTrucks->getSize() + vipTrucks->getSize();

	userInterface->print(totalSize);
	userInterface->print(" Empty Trucks:	");

	// normalCargos
	userInterface->print("[");
	normalTrucks->printQueue();
	userInterface->print("]");

	// specialCargos
	userInterface->print("(");
	specialTrucks->printQueue();
	userInterface->print(")");

	// vipcargos
	userInterface->print("{");
	vipTrucks->printQueue();
	userInterface->print("}", true);


	userInterface->print("----------------------------------------------------------", true);

}

void Company::printLoadingTrucks()
{

	userInterface->print(loadingTrucks->getSize());
	userInterface->print(" Loading Trucks:	");

	Trucks* temp;

	for (int i = 0; i < loadingTrucks->getSize(); i++)
	{

		// print id
		loadingTrucks->dequeue(temp);
		userInterface->print(temp->getId());
		loadingTrucks->enqueue(temp);

		// print list
		Type type = temp->getTruckType();
		switch (type)
		{
		case NORMAL:
			userInterface->print("[");
			temp->printCargos();
			//userInterface->print(", ");
			//temp->getMovingTime()->print(false);
			userInterface->print("]");

			break;

		case SPECIAL:
			userInterface->print("(");
			temp->printCargos();
			//userInterface->print(", ");
			//temp->getMovingTime()->print(false);
			userInterface->print(")");
			break;

		case VIP:
			userInterface->print("{");
			temp->printCargos();
			//userInterface->print(", ");
			//temp->getMovingTime()->print(false);
			userInterface->print("}");
			break;
		}

	}

	userInterface->print("", true);
	userInterface->print("----------------------------------------------------------", true);

}

void Company::printIncheckupTrucks()
{

	userInterface->print(inCheckupNormalTrucks->getSize() + inCheckupSpecialTrucks->getSize() + inCheckupVipTrucks->getSize());
	userInterface->print(" Checkup Trucks:		");

	inCheckupNormalTrucks->printQueue();
	inCheckupSpecialTrucks->printQueue();
	inCheckupVipTrucks->printQueue();
	
	userInterface->print("", true);
	userInterface->print("----------------------------------------------------------", true);

}

void Company::printMovingCargos()
{

	userInterface->print(movingTrucks->getSize());
	userInterface->print(" Moving Cargos:		");

	Trucks* curr;
	LinkedQueue<Trucks*> tmp;

	int s = movingTrucks->getSize();
	for (int i = 0; i < s; i++)
	{
		movingTrucks->dequeue(curr);
		userInterface->print(curr->getId());
		// truck priority
		tmp.enqueue(curr);
		Type k = curr->getTruckType();

		switch (k)
		{
		case  NORMAL:
			userInterface->print("[");
			curr->printCargos();
			//userInterface->print(", ");
			//(*curr->getDeliveryInterval() + *curr->getMovingTime()).print(false);
			userInterface->print("]");

			break;

		case SPECIAL:
			userInterface->print("(");
			curr->printCargos();
			//userInterface->print(", ");
			//(*curr->getDeliveryInterval() + *curr->getMovingTime()).print(false);
			userInterface->print(")");
			break;

		case VIP:

			userInterface->print("{");
			curr->printCargos();
			//userInterface->print(",");
			//(*curr->getDeliveryInterval() + *curr->getMovingTime()).print(false);
			userInterface->print("}");
			break;
		}

	}

	while (tmp.dequeue(curr))
		addMovingTrucks(curr);

	userInterface->print("", true);
	userInterface->print("----------------------------------------------------------", true);

}


void Company::printWaitingCargos()
{

	int totalSize = normalCargos->getSize() + specialCargos->getSize() + vipCargos->getSize();

	userInterface->print(totalSize);
	userInterface->print(" Waiting Cargos:	");

	// normalCargos
	userInterface->print("[");
	normalCargos->PrintList();
	userInterface->print("]");

	// specialCargos
	userInterface->print("(");
	specialCargos->printQueue();
	userInterface->print(")");

	// vipcargos
	userInterface->print("{");
	vipCargos->printQueue();
	userInterface->print("}");

	userInterface->print("", true);
	userInterface->print(" ----------------------------------------------------------", true);

}

void Company::printDeliveredCargos()
{

	userInterface->print(deliveredCargos->getSize());
	userInterface->print(" Delivered Cargos:		");

	Cargos* curr;
	int s = deliveredCargos->getSize();
	for (int i = 0; i < s; i++)
	{

		deliveredCargos->dequeue(curr);

		Type k = curr->getCargoType();

		switch (k)
		{
		case NORMAL:
			userInterface->print("[");
			userInterface->print(curr->getId());
			userInterface->print("]");

			break;

		case SPECIAL:
			userInterface->print("(");
			userInterface->print(curr->getId());
			userInterface->print(")");
			break;

		case VIP:
			userInterface->print("{");
			userInterface->print(curr->getId());
			userInterface->print("}");
			break;
		}

		deliveredCargos->enqueue(curr);

	}
	userInterface->print("", true);
	userInterface->print(" ----------------------------------------------------------", true);

}

void Company::autoPromotion()
{
	//autop given 8
	//currrent time
	// event time
	Cargos* cargo = nullptr;

	if (normalCargos->getSize() == 0)
		return;

	cargo = normalCargos->GetFirstObj();

	while (*currentTime - cargo->getPreparationTime() >= Time(autoP, 0))
	{
		//promote
		removeNormalCargo(cargo, cargo->getId());
		cargo->setCargoType(VIP);
		addVipCargo(cargo);
		numAutoPromoted++;
		numNormalCargos--;
	}
}

void Company::truckLoadToMove()
{
	// it is all about load time in cargo
	// currenty time - time in loading == sum of load cargos

	// we should add move truck to simulate

	// condition -> capacity = max
	Trucks* truck = nullptr;
	// ymkn n7tago fl simulate

	for (int i = 0, z = loadingTrucks->getSize(); i < z; i++)
	{

		loadingTrucks->dequeue(truck);

		if (*currentTime >= *truck->getMovingTime())
		{

			// loading trucks	(delivery time)
			// moving trucks	(update delivery time)
			truck->updateDeliveryTime();
			addMovingTrucks(truck);

			// increament journeys
			truck->incNumOfJourneys();
			truck->calcDeliveryInterval();

		}
		else addLoadingTruck(truck);

	}

	// once occured
	// remove from loading and add to moving list

	/*
	LinkedQueue<Trucks*>* normalTrucks;			// available - Empty
	LinkedQueue<Trucks*>* specialTrucks;		//available - Empty
	LinkedQueue<Trucks*>* vipTrucks;			// available - Empty
	*/

	// PriorityQueue<Trucks*>* movingTrucks;			//delivering

}

void Company::truckMoveToAvailOrCheck()
{

	Trucks* truck = nullptr;
	LinkedQueue<Trucks*> tmp;
	// condition duration time
	// getDeliveryInterval() == (current time - time truck started moving)
	for (int i = 0, z = movingTrucks->getSize(); i < z; i++)
	{
		movingTrucks->dequeue(truck);

		deliverCargos(truck);

		if (*truck->getDeliveryInterval() <= (*currentTime - *truck->getMovingTime()))
		{

			addTotalActivetime(truck);
			truck->setLoadTime(0);

			// checkup
			if (truck->getJourneysBeforeCheckup() == truck->getNumberOfJourneys())
			{
				//reset number of journeys
				truck->setNumberOfJourneys(0);

				// add to checkup list
				switch (truck->getTruckType())
				{
				case NORMAL:

					addCheckupNormalTruck(truck);
					break;

				case SPECIAL:

					addCheckupSpecialTruck(truck);
					break;

				case VIP:

					addCheckupVipTruck(truck);
					break;

				}

			}
			// available
			else
			{
				// Add available truck with respect to type
				switch (truck->getTruckType())
				{
				case NORMAL:

					addNormalTruck(truck);
					break;

				case SPECIAL:

					deliverCargos(truck);
					addSpecialTruck(truck);
					break;

				case VIP:

					addVipTruck(truck);
					break;

				}
			}
		}
		else
			tmp.enqueue(truck);
	}

	while (tmp.dequeue(truck))
		addMovingTrucks(truck);

}

void Company::truckCheckToAvail()
{

	Trucks* truck = nullptr;

	// condition
	// (current time - time when checkup) == maintenance time

	// Normal
	for (int i = 0, z = inCheckupNormalTrucks->getSize(); i < z; i++)
	{
		inCheckupNormalTrucks->dequeue(truck);


		// currentTime = duration + deliveryInterval + movingTime 
		if (*currentTime >= *truck->getCheckupDuration() + *truck->getMovingTime() + *truck->getDeliveryInterval())
		{

			addNormalTruck(truck);

		}
		else addCheckupNormalTruck(truck);
	}

	// Special
	for (int i = 0, z = inCheckupSpecialTrucks->getSize(); i < z; i++)
	{
		inCheckupSpecialTrucks->dequeue(truck);

		if (*currentTime >= *truck->getCheckupDuration() + *truck->getMovingTime() + *truck->getDeliveryInterval())
		{

			addSpecialTruck(truck);

		}
		else addCheckupSpecialTruck(truck);
	}

	// VIP
	for (int i = 0, z = inCheckupVipTrucks->getSize(); i < z; i++)
	{
		inCheckupVipTrucks->dequeue(truck);

		if (*currentTime >= *truck->getCheckupDuration() + *truck->getMovingTime() + *truck->getDeliveryInterval())
		{

			addVipTruck(truck);

		}
		else addCheckupVipTruck(truck);
	}

	// maintenance time 



	//move from check to avail wrt type

}

void Company::deliverCargos(Trucks* truck)
{

	Cargos* cargo = nullptr;
	LinkedQueue<Cargos*> tmp;

	while (truck->removeCargo(cargo))
	{

		// no need to remove truck pointer from cargo... to be used in output file
		if (*cargo->getDeliveryTime() <= *currentTime)
		{

			incNumOfCargos(cargo->getCargoType());
			deliveredCargos->enqueue(cargo);
			truck->incremnetNumOfCargos();

		}
		else
			tmp.enqueue(cargo);

	}

	while (tmp.dequeue(cargo))
		truck->addCargo(cargo);

}

void Company::incNumOfCargos(Type type)
{
	switch (type)
	{
	case NORMAL:
		numNormalCargos++;
		break;
	case VIP:
		numVipCargos++;
		break;
	case SPECIAL:
		numSpecialCargos++;
		break;
	}
}

void Company::decNumOfCargos(Type type)
{
	switch (type)
	{
	case NORMAL:
		numNormalCargos--;
		break;
	case VIP:
		numVipCargos--;
		break;
	case SPECIAL:
		numSpecialCargos--;
		break;
	}
}

int Company::getTotalWaitingTime()
{
	Time time(0, 0);
	Cargos* cargo;

	for (int i = 0, z = deliveredCargos->getSize(); i < z; i++)
	{
		deliveredCargos->dequeue(cargo);
		time = time + cargo->getWaitingTime();
		deliveredCargos->enqueue(cargo);
	}

	return time.timeInHours();
}

void Company::addTotalActivetime(Trucks* truck)
{

	totalActiveTime += truck->getTruckActiveTime().timeInHours();

}

float Company::avgPercentageActiveTime()
{

	Trucks* truck = nullptr;
	float percentageNormal = 0;
	float percentageSpecial = 0;
	float percentageVip = 0;


	// Normal
	for (int i = 0, n = normalTrucks->getSize(); i < n; i++)
	{

		normalTrucks->dequeue(truck);
		percentageNormal += (float) truck->getTruckActiveTime().timeInHours() / currentTime->timeInHours();
		normalTrucks->enqueue(truck);

	}

	// Special
	for (int i = 0, z = specialTrucks->getSize(); i < z; i++)
	{
		specialTrucks->dequeue(truck);
		percentageSpecial += (float) truck->getTruckActiveTime().timeInHours() / currentTime->timeInHours();
		specialTrucks->enqueue(truck);
	}

	// Vip
	for (int i = 0, z = normalTrucks->getSize(); i < z; i++)
	{
		vipTrucks->dequeue(truck);
		percentageVip += (float) truck->getTruckActiveTime().timeInHours() / currentTime->timeInHours();
		vipTrucks->enqueue(truck);

	}

	return (percentageNormal + percentageSpecial + percentageVip) / 3;
}

float Company::getTotalUtilizationTime()
{

	Trucks* truck = nullptr;

	float totalUtilization = 0;


	for (int i = 0, z = normalTrucks->getSize(); i < z; i++)
	{
		normalTrucks->dequeue(truck);
		totalUtilization = totalUtilization + truck->calcUtilization(currentTime);
		normalTrucks->enqueue(truck);
	}

	for (int i = 0, z = specialTrucks->getSize(); i < z; i++)
	{
		specialTrucks->dequeue(truck);
		totalUtilization = totalUtilization + truck->calcUtilization(currentTime);
		specialTrucks->enqueue(truck);
	}

	for (int i = 0, z = vipTrucks->getSize(); i < z; i++)
	{
		vipTrucks->dequeue(truck);
		totalUtilization = totalUtilization + truck->calcUtilization(currentTime);
		vipTrucks->enqueue(truck);
	}

	return totalUtilization / 3;

}


// Destructor
Company::~Company()
{
	delete normalTrucks;
	delete specialTrucks;
	delete vipTrucks;
	delete loadingTrucks;
	delete inCheckupNormalTrucks;
	delete inCheckupSpecialTrucks;
	delete inCheckupVipTrucks;
	delete movingTrucks;

	delete normalCargos;
	delete specialCargos;
	delete vipCargos;

	// nesina nefady el delivered abl ma n delete el list!
	//while(removeDeliveredCargo())
	delete deliveredCargos;

	delete userInterface;
}
