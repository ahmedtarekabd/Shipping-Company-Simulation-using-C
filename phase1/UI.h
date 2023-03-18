#pragma once
#include "Enums.h"
#include "LinkedQueue.h"
#include "LinkedList.h"
#include "PriorityQueue.h"
#include "Trucks.h"
#include "Cargos.h"
#include "Enums.h"
#include "Company.h"

#include <iostream>
#include <Windows.h>
using namespace std;


//		Current time(Day:Hour):70:9

//      7 waiting cargos: [110,113] (116,118) {119,112,114}
//-----------------------------------------------------------
//      4 Loading Trucks: 5[3,4,12,15] 1(6) 7{9,11} 2[5,7]
//-----------------------------------------------------------
//      4 Empty trucks: [4], (10), [6], {8}
//-----------------------------------------------------------
//      5 Moving cargos: 7[45, 52] 12{34, 77, 80}
//-----------------------------------------------------------
//      2 In-Checkup Trucks: [2] {3}
//-----------------------------------------------------------
//      3 Delivered Cargos: {5} [4] (1)
//-----------------------------------------------------------


//-----------------------------------------------------------
//  Numbers shown are IDs of cargos and trucks
// 
//	[] -> Normal 
//	() -> special
//	{} -> VIP
//
//	line 3 means: truck 7 is being loaded by VIP cargos 9,11
// 
//-----------------------------------------------------------

class Company;

class UI
{

	// Not important
	UIModes mode;
	Company* company;
	bool firstEnter;

public:

	UI(Company* comp);


	//main functions in UI

	string startSimulation();
	void selectMode();
	void endSimulation();

	// simulate the needed mode
	void simulateMode();

	// wait for user input in order to return back to company class, simulate function
	void interactiveMode();

	// delay a second then return to simulate function
	// phase 2
	void stepByStepMode();

	// just print the state of the program
	// "Silent Mode", "Simulation starts...", "Simulation ends, Output file created" 
	// then printes output file when the simulation ends without displaying in the console the lists
	// phase 2
	void silentMode();


	//Print Functions
	void PrintTime(Time* currentTime);
	void printLists();
	// error when write wrong input
	void wronginput();
	void print(string text, bool newLine = false);
	void print(int num, bool newLine = false);

	~UI();

};
