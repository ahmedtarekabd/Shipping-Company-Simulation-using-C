#include "UI.h"
#include <string>

UI::UI(Company* comp)
{
	company = comp;
	firstEnter = true;
}

string UI::startSimulation()
{

	string fileName;

	// Greatings
	cout << "======== Hello, Start Simulation =========" << endl;
	
	// Get input file name  *** do in main or start simulation
	cout << "Enter input File name: ";

	cin >> fileName;
	string extension = ".txt";

	// adds extension (.txt) to fileName if not entered by the user
	if (fileName.find(extension) != std::string::npos)
		return fileName;
	else
		return fileName + extension;

}

void UI::selectMode()
{
	int modeSelection;

	// get mode from user
	cout << "Enter Mode: 1: Interactive Mode, 2: StepByStep Mode,  3: Silent Mode ";

	cin >> modeSelection;

	//Validation
	while (modeSelection != 1 && modeSelection != 2 && modeSelection != 3)
	{
		cout << "Error!! Please enter a valid mode: ";
		cin >> modeSelection;
	}

	switch (modeSelection)
	{
	case 1:
		mode = INTERACTIVE;
		cout << "========== Interactive Mode ==========" << endl;
		break;

	case 2:
		mode = STEPBYSTEP;
		cout << "========== Step by Step Mode ==========" << endl;
		break;

	case 3:
		mode = SILENT;
		cout << "========== Silent Mode ==========" << endl;
		break;
	}

}

void UI::endSimulation()
{

	if (mode == SILENT)
	{

		cout << "Simulation ends, Output file created" << endl;

	}
	else
		cout << "========= Simulation End =========" << endl;
}

void UI::interactiveMode()
{

	// printLists
	printLists();

	// wait for enter key to increament hour and make action

	if (firstEnter)
	{
		cin.ignore(); // clears all previous inputs
		firstEnter = false;
	}

	cout << "======== Press Enter to continue ========";
	cin.get();
}

void UI::stepByStepMode()
{

	// printLists
	printLists();

	// increament hour every one seconds

	Sleep(1000); // wait one second
}

void UI::silentMode()
{
	// select mode already prints it
	// cout << "Silent Mode" << endl;
	if (firstEnter)
	{
		cout << "Simulation Starts..." << endl;
		firstEnter = false;
	}


}

void UI::PrintTime(Time* currentTime)
{
	cout << "Current Time (Day:Hour) : ";
	currentTime->print();
}

void UI::printLists()
{

	PrintTime(company->getCurrentTime());
	company->printWaitingCargos();
	company->printLoadingTrucks();
	company->printEmptyTrucks();
	company->printMovingCargos();
	company->printIncheckupTrucks();
	company->printDeliveredCargos();

}

void UI::wronginput()
{

	cout << endl << "You reached maximum number of wrong inputs" << endl;

}


void UI::print(string text, bool newLine)
{

	cout << text;
	if (newLine)
		cout << endl;

}

void UI::print(int num, bool newLine)
{

	cout << num;
	if (newLine)
		cout << endl;

}

void UI::simulateMode()
{
	switch (mode)
	{
	case INTERACTIVE:

		interactiveMode();
		break;

	case STEPBYSTEP:

		stepByStepMode();
		break;

	case SILENT:

		silentMode();
		break;
	}
}

UI::~UI()
{
}
