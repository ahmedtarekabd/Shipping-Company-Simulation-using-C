#pragma once

#include "Enums.h"
#include "Cargos.h"
#include "LinkedQueue.h"

class Trucks
{

	Type truckType;
	Type cargosType;				// Types of cargos loaded (for approveLoadingTruck in Company)
	int totalNumOfCargos;
	int numOfJourneys;
	int totalNumOfJourneys;
	int truckCapacity;
	int speed;
	int JourneysBeforeCheckup;	// The number of journeys the truck complete before a checkup
	int ID;						// Truck id
	Time* loadTime;				// time when truck go to load
	Time* movingTime;			// time when truck start moving
	Time* checkupDuration;		// Checkup duration
	Time* deliveryInterval;		// Time Truck go back to Avail/Checkup

	Time truckActiveTime;		// Time where truck is loading or delivering

	//int utilization;
	//Finish time: deliveryInterval + movingTime + sum of delivery time

	// Must be priority queue (priority: Delivery Time)
	PriorityQueue<Cargos*, Time>* cargos; // Cargos List in the truck

	// Number of trucks
	static int numberOfNTrucks;
	static int numberOfSTrucks;
	static int numberOfVTrucks;


	
public:

	Trucks(int id);
	Trucks(int mt, int tc, int s, int jbc, int id, Type t);
	

	// Setters
	void setTruckType(Type t);
	void setTruckCapacity(int tc);
	void setSpeed(int s);
	void setJourneysBeforeCheckup(int jbc);
	void setMovingTime(Time* time);
	void incNumOfJourneys();
	void setNumberOfJourneys(int numOfJour);
	void incremnetNumOfCargos();
	void calcDeliveryInterval();
	float calcUtilization(Time* simTime);
	void setLoadTime(Time time);

	// Getters
	Type getTruckType();
	Type getCargosType();
	int getTruckCapacity();
	int getSpeed();
	int getJourneysBeforeCheckup();
	int getId();
	int getTotalNumberOfJourneys();
	int getNumberOfJourneys();
	int getNumOfCargos();
	int getNumberofCargosInTruck();
	Time* getLoadTime();
	Time* getMovingTime();
	Time* getCheckupDuration();
	Time* getDeliveryInterval();
	Time getTruckActiveTime(); // get truck active time in hours
	

	// increment number of trucks
	static void incrementNumberOfTrucks(Type type);
	static void decrementNumberOfTrucks(Type type);
	static int getNumberOfTrucks(Type type);

	// Cargos in truck Functions
	//PriorityQueue<Cargos*, Time>* getCargosInTrucks();

	// return sum of load cargos time
	//int totalLoadTime();
	
	// Add and Remove Cargo 
	bool addCargo(Cargos* c);
	bool removeCargo(Cargos*& cargo);
	void printCargos();

	void updateDeliveryTime();

	bool operator == (const Trucks& other);

	~Trucks();

};

