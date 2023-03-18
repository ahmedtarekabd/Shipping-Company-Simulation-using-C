#pragma once

#include "Enums.h"
#include "Time.h"
#include "LinkedQueue.h"
#include "PriorityQueue.h"

class Trucks;

class Cargos
{
	Type cargoType;             // determining type of cargo wether its (normal,special,vip)
	Time preparationTime;       // preparation time of cargo
	int loadUnloadTime;			// In hours
	int deliveryDistance;       // delivery distance of cargo
   	int cost;                   // cargo Cost
	int ID;                     // cargo ID
	bool isAutoP;				// check wether cargo is on autopromotion or not
	bool isMaxW;				// check wether cargo waited maximum time or not

	Time* deliveryTime;
	Time* prevUnloadTimes;

	Trucks* truck;				// To calculate the delivery time

	int priority;               

	void calcPriority();        // calculating the priority according to the cost and delivery distance and preparation time. 

	//AutoP & MaxW should be in company as they are constant to all

public:

	Cargos(int id);							// searching using ID
	Cargos(Time pt, int lt, int dd, int c,int id, Type t);

	// Setters and getters

	void setCargoType(Type t);             // setting cargos' type
	void setPreparationTime(Time pt);      // setting cargos' preparation time
	void setLoadUnloadTime(int lt);        // setting cargos' load & unload time
	void setDeliveryDistance(int dt);      // setting cargos' delivery distance
	void setCost(int c);                   // setting cargos' cost
	void setId(int id);                    // setting cargos' ID
	void setIsAutoP(bool ap);              // setting cargos' pormotion 
	void setIsMaxW(bool mw);               // setting cargos' maximum waiting time
	void setTruck(Trucks* t);

	Type getCargoType();                   // getting cargo type
	Time getPreparationTime();             // getting preparation time
	int getLoadUnloadTime();               // getting load & unload time
	int getDeliveryDistance();             // getting cargo delivery distance
	void addCost(int extraMoney);          // adding extra money to the cost of cargo
	int getCost();                         // getting cargos' cost
	int getId();                           // getting cargos' ID
	bool IsAutoP();                        // check wether cargo is on autopromotion or not
	bool IsMaxW();                         // check wether cargo waited maximum time or not
	int getTruckId();
	Time* getMovingTime();
	Time getWaitingTime();

	
	void calcDeliveryTime();
	Time* getDeliveryTime();
	void updateDeliveryTime(Time* time);
	int getPriority();                     // getting priority which is has been calculated through calcPriority()

	bool operator == (const Cargos & other);
};
