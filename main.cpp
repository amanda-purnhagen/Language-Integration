/*
 *  Language Integration Project
 *
 *  Name:            Amanda Purnhagen
 *  Date:            22 August 2021
 *  Program Purpose: The purpose of this program is to learn how to integrate Python code and C++ code.
 *					 The following code within main.cpp includes functions that allow the communication 
 *					 between the two languages. It also contains code that asks the user for the name of
 *					 a file containing items bought at a grocery store in chronological order. It then 
 *					 displays a menu to the user who may then select their choice. Their choice then
 *					 determines which Python function will be executed and what information about the
 *					 grocery store will be displayed.
 */

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonFile");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonFile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonFile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Displays a menu in a loop to the user from which they are prompted to choose an option. Takes in a file name as a parameter.
void displayMenu(string userFileName) {
	// Determines whether the following while loop will continue running.
	bool keepRunning = true;

	// Checks if keepRunning is true. While true, it displays the following menu to the user.
	while (keepRunning) {
		// Holds the value of the user's menu choice.
		int userMenuChoice;

		// Displays a menu to the user, presenting options to display data about the grocery items purchased.
		cout << "Please choose an option from the following menu:" << endl << endl;
		cout << "1) See a list of all items purchased in a given day and the number of times each item was purchased." << endl;
		cout << "2) See the number representing how many times a specific item was purchased in a given day." << endl;
		cout << "3) See a text-based histogram listing all items purchased in a given day, along with a representation of the number of times each item was purchased." << endl;
		cout << "4) Exit the program." << endl << endl;
		cout << "Enter your selection as a number: 1, 2, 3, or 4: ";

		// userMenuChoice holds the integer of the menu option that the user chose.
		cin >> userMenuChoice;

		// The first three options in the following if-else statement use the prewritten C++ function "callIntFunc" that links C++ code to Python code.

		// If the user decided to see a list of all items purchased in a given day and the number of times each item was purchased,
		// Python function "ListAllItemsQuantity" will be called with parameter userFileName.
		if (userMenuChoice == 1) {
			char returnChoice;

			cout << callIntFunc("ListAllItemsQuantity", userFileName);
			
			keepRunning = true;
		}
		// If the user decided to see the number representing how many times a specific item was purchased in a given day, Python
		// function "SpecificItemCount" will be called with parameter userFileName. 
		else if (userMenuChoice == 2) {
			cout << callIntFunc("SpecificItemCount", userFileName);

			keepRunning = true;
		}
		// If the user decided to see a text-based histogram listing all items purchased in a given day, along with a representation of the number of
		// times each item was purchased, Python function "DisplayQuantityHistogram" will be called with parameter userFileName.
		else if (userMenuChoice == 3) {
			cout << callIntFunc("DisplayQuantityHistogram", userFileName);

			keepRunning = true;
		}
		// If the user decided to exit the program, then the while loop will end and the program will close.
		else if (userMenuChoice == 4) {
			cout << "Goodbye." << endl;

			keepRunning = false;
			exit(0);
		}
		// If the user enters anything other than 1, 2, 3, or 4, then they will get a message saying their entry was invalid. Then the menu will
		// display again.
		else {
			cout << "Invalid entry. Please try again." << endl;

			displayMenu(userFileName);
		}
	}
}

int main()
{
	// Holds the user's input for the file name.
	string userFileName;

	// 
	cout << "Please enter the name of the file that contains a list of all items purchased in chronological order." << endl;
	cout << "Please note that the file must be in the same directory as this program, otherwise you must provide its full path: ";

	// Stores the user's input into variable userFileName.
	cin >> userFileName;

	// Calls the displayMenu function with the user's file name as a parameter.
	displayMenu(userFileName);

	return 0;
}