#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "LinkedQueue.h"
#include "LinkedList.h"
#include "PriorityQueue.h"
#include "Trucks.h"
#include "Cargos.h"
#include "Enums.h"
#include "UI.h"


using namespace std;

class Event;
class Time;
class UI;

class Company
{

	// Events -> queue
	// Trucks
	//		VIP, Normal, Special -> Queue for each type (as empty trucks)
	//		Loading Trucks
	//		Maintainance (checkup)
	//		Moving Trucks
	//	
	// Cargos -> 
	//		Types -> VIP priority Queue
	//			  -> Special Queue
	//			  -> Normal Linked List
	//		loading cargos -> Queue
	//		loaded cargos -> Queue
	//		delivered -> Queue
	// 
	// 
	
	// Data from ReadFile
	
	// Trucks Data
	int N, S, V;
	int NS, SS, VS;
	int NTC, STC, VTC;
	int J, CN, CS, CV;
	int AutoP, MaxW;
	char doubleDot;

	int totalActiveTime;

	// Cargos Data
	int numNormalCargos = 0;
	int numAutoPromoted = 0;
	int numSpecialCargos = 0;
	int numVipCargos = 0;


	// Events Data
	int NumOfEvents;
	char eventType;
	char TYPChar;
	Type TYP;
	int ID, DIST, LT, Cost, ExtraMoney;
	Time ET;
	int day, hour;


	Time* currentTime; 

	int normalTrucksInfo[DATASIZE];
	int specialTrucksInfo[DATASIZE];
	int vipTrucksInfo[DATASIZE];

	int autoP;			// promotion limit (days)
	int maxWait;				// max waiting time (hours)

	// Events List
	LinkedQueue<Event*>* events;

	// Trucks Lists
	LinkedQueue<Trucks*>* normalTrucks;			// available - Empty
	LinkedQueue<Trucks*>* specialTrucks;		//available - Empty
	LinkedQueue<Trucks*>* vipTrucks;			// available - Empty
	// Optional
	LinkedQueue<Trucks*>* loadingTrucks;		//loading


	// check-up one for each truck
	// each our check for checkup duration from each empty truck list (make a function)
	LinkedQueue<Trucks*>* inCheckupNormalTrucks;	// incheckup
	LinkedQueue<Trucks*>* inCheckupSpecialTrucks;	// incheckup
	LinkedQueue<Trucks*>* inCheckupVipTrucks;		// incheckup
	// Must be priority queue, named movingTrucks
	// (priority: delivery time of the first cargo in each truck)
	PriorityQueue<Trucks*, Time>* movingTrucks;		//delivering

	// Cargos Lists
	LinkedList<Cargos*>* normalCargos;			// waiting
	LinkedQueue<Cargos*>* specialCargos;		// waiting
	PriorityQueue<Cargos*, int>* vipCargos;		// waiting
	LinkedQueue<Cargos*>* deliveredCargos;		// delivered


	//user interface
	UI* userInterface;


public:

	// Default Constructor
	Company();


	// ========== Files ==========
	// Read File Function
	bool ReadFile(string fileName);

	// Write File Function
	void WriteFile();


	// ========== Getters ==========
	Time* getCurrentTime();

	// ========== Adding ==========
	// Add Event
	void addEvent(Event* event);

	// Add Trucks
	void addNormalTruck(Trucks* truck);
	void addSpecialTruck(Trucks* truck);
	void addVipTruck(Trucks* truck);
	void addLoadingTruck(Trucks* truck);
	void addCheckupNormalTruck(Trucks* truck);
	void addCheckupSpecialTruck(Trucks* truck);
	void addCheckupVipTruck(Trucks* truck);
	void addMovingTrucks(Trucks* truck);

	// Add Cargos
	void addNormalCargo(Cargos* cargo);
	void addSpecialCargo(Cargos* cargo);
	void addVipCargo(Cargos* cargo);
	void addDeliveredCargo(Cargos* cargo);

	// ========== Removing ==========
	// Event
	bool removeEvent();

	// Trucks
	bool removeNormalTruck(Trucks*& truck);
	bool removeSpecialTruck(Trucks*& truck);
	bool removeVipTruck(Trucks*& truck);
	bool removeLoadingTruck(Trucks*& truck);
	bool removeInCheckupNormalTruck(Trucks*& truck);
	bool removeInCheckupSpecialtrucks(Trucks*& truck);
	bool removeInCheckupViptrucks(Trucks*& truck);
	bool removeMovingTruck(Trucks*& truck, int id);

	// Cargos
	// Search by ID to remove
	bool removeNormalCargo(Cargos*& cargo, int id);
	bool removeNormalCargoBeg(Cargos*& cargo);
	bool removeSpecialCargo(Cargos*& cargo, int id);
	bool removeVipCargo(Cargos*& cargo, int id);
	bool removeDeliveredCargo(Cargos*& cargo, int id); // no function is called


	// ========== Assignment ==========
	void assignTrucks();
	void assignNormalCargo();
	void assignSpecialCargo();
	void assignVipCargo();
	void assignLoadingTruck(Trucks* truck);
	bool approveLoadingTruck(Type type);
	void assignLoadingCargo(Cargos* cargo);
	void assignMaintainanceCargo(Cargos* cargo);
	void assignMovingCargo(Cargos* cargo);
	void maxWNormalCargos();
	void maxWSpecialCargos();

	// Change Type 
	void changeType(Cargos* cargo, int cargoID, Type newtype);
	Type getType(char type);


	// Working Hours function returns bool according to current time
	bool inWorkingHours();

	// ========== Simulation ==========

	void simulatePhase1();
	void simulate();
	// call the event at certain time
	void excuteEvents();
	bool simulationEnds();

	// ========== Print Lists ==========

	void printEmptyTrucks();		// Available
	void printLoadingTrucks();		// Loading
	void printIncheckupTrucks();	// Checkup
	//void printIncheckupSpecialTrucks();
	//void printIncheckupVipTrucks();
	void printMovingCargos();		// Moving
	void printWaitingCargos();		// Waiting
	void printDeliveredCargos();	// Delivered

	// autopromotion
	void autoPromotion();

	// MovingTruck
	void truckLoadToMove();				// Done
	void truckMoveToAvailOrCheck();		// Done
	void truckCheckToAvail();			// Done
	void deliverCargos(Trucks* truck);	// Done

	// 3ayzin b3d ma n3mel nwady el truck lel available/checkup...
	// ne reset data members le default values


	// number Of cargos after calling events
	void incNumOfCargos(Type type);
	void decNumOfCargos(Type type);

	// get total waiting time of cargos in terms of hours
	int getTotalWaitingTime();

	// gets called in truckMoveToAvailOrCheck
	void addTotalActivetime(Trucks* truck);
	float avgPercentageActiveTime();

	float getTotalUtilizationTime();
	//Destructors
	~Company();

};