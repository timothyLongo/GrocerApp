// Timothy Longo
// Project 3 -- Grocery App

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <iomanip> // for text formatting
#include <fstream> // for reading the frequency.dat file, for option 3 histogram
#include <vector> // used for reading of frequency.dat file


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
	PyObject* my_module = PyImport_ImportModule("myfirstprogram");
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
	pName = PyUnicode_FromString((char*)"myfirstprogram");
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
	pName = PyUnicode_FromString((char*)"myfirstprogram");
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

void Menu() {
	bool keepLoopin = true;
	cout << setw(51) << setfill('=') << "" << endl;
	cout << ">" << setw(7) << setfill(' ') << "" << "Welcome to the Corner Grocer App =D" << setw(7) << "" << "<" << endl;
	cout << setw(51) << setfill('=') << "" << endl << endl;
	while (keepLoopin) {
		string userIn; // uses string variable so cin never fails. easy to validate this way
		cout << setw(51) << setfill('_') << "" << endl;
		cout << "|" << setw(22) << setfill(' ') << "" << "MENU" << setw(23) << "" << "|" << endl;
		cout << setw(51) << setfill('-') << "" << endl;
		cout << "[ 1 ]  Print list of items sold with frequency" << endl;
		cout << "[ 2 ]  Print frequency of a specific item" << endl;
		cout << "[ 3 ]  Print histogram of items sold with frequency" << endl;
		cout << "[ 4 ]  Exit" << endl;
		cout << setw(51) << "" << endl << endl;
		cout << setw(9) << "" << "Enter your selection : " << endl;
		cin >> userIn;
		if (userIn.at(0) == '1') {
			system("CLS");
			cout << setw(39) << setfill('_') << "" << endl;
			cout << "|" << setw(6) << setfill(' ') << "" << "ITEMS SOLD WITH FREQUENCY" << setw(6) << "" << "|" << endl;
			cout << setw(39) << setfill('-') << "" << endl;
			CallProcedure("theList"); // calls Python function, 0 parameters, void return type
		}
		else if (userIn.at(0) == '2') {
			string itemName;
			cout << setw(9) << "" << "Enter item name :" << endl;
			cin >> itemName;
			system("CLS");
			cout << setw(20) << setfill('_') << "" << endl;
			cout << "|  ITEM  |   FREQ   |" << endl;
			cout << setw(20) << setfill('-') << "" << endl;
			cout << " " << setw(12) << setfill(' ') << left << itemName;
			cout << setw(5) << setfill(' ') << right << callIntFunc("returnFreq", itemName) << endl; // calls Python funtion named "returnFreq" with a string parameter
		}
		else if (userIn.at(0) == '3') {
			CallProcedure("writeTheFile"); // python created the frequency.dat file in my docs
			// now we open and read it with C++
			// ifstream reads from files
			vector<string> itemVec; // stores all items from file
			vector<int> freqVec; // stores all freq from file

			ifstream reader; // declares reading variable of ifstream
			reader.open("C:\\Users\\Timmy\\Documents\\frequency.dat");

			string item; // local variables declared for the purpose of storing in vector
			int freq;

			if (reader.is_open()) {
				while (!reader.eof() && !reader.fail()) {
					reader >> item;
					reader >> freq;
					itemVec.push_back(item); // populates vector
					freqVec.push_back(freq);
					// note that each index is corresponding to one another
					// index 10 of item corresponds to index 10 of freq
					// this logic allows the below 'for' loop to work
				}
			}
			system("CLS");
			cout << setw(25) << setfill('_') << "" << endl;
			cout << "|" << setw(7) << setfill(' ') << "" << "HISTOGRAM" << setw(7) << "" << "|" << endl;
			cout << setw(25) << setfill('-') << "" << endl;
			for (unsigned int i = 0; i < freqVec.size() - 1; ++i) {
				cout << setw(12) << setfill(' ') << left << itemVec.at(i) << " " << setw(12) << right << string(freqVec.at(i), '*') << endl;
			}				// neat string(int, char) for repeating char n times
			// the for loop pulls from the vector elements to create the histogram
			
		}
		else if (userIn.at(0) == '4') {
			exit(0);
		}
		else {
			system("CLS");
			cout << setw(51) << setfill('=') << "" << endl;
			cout << ">" << setw(12) << setfill(' ') << "" << "Invalid input - try again" << setw(12) << "" << "<" << endl;
			cout << setw(51) << setfill('=') << "" << endl << endl;
		}
	}
}

void main()
{
	Menu();
}