#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

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
	PyObject* my_module = PyImport_ImportModule("PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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

void menuDisplay() {
	
		//Display Menu to user.
		cout << "Please choose one of the following options" << endl;
		cout << "1. Display Items & their frequency" << endl;
		cout << "2. Display a specific item and it's frequency" << endl;
		cout << "3. Create a histogram of each itema & their frequency" << endl;
		cout << "4. Exit the program" << endl;
}


void displayEachItem() {
	CallProcedure("display_each_item"); //Calls Python Function for 1st menu choice
	

}

void displaySpecificItem() {
	
	cout << "Please enter the item you wish to display" << endl; 

	//Creating Variables for data in input file to pass to python
	string item;

	cin >> item;
	if (cin.fail()) { //if the user input isn't string
		cout << "Invalid Input" << endl;
	}
	int itemCount = callIntFunc("display_specific_item", item);
	cout << item << ":" << itemCount << endl;



}

void displayHistogram() {
	
	CallProcedure("read_write_list"); //call python function to create .dat
	ifstream inFS;
	inFS.open("frequency.dat");

	string item;
	int count;

	inFS >> item;
	inFS >> count;
	 
	if (!inFS.is_open()) { //If file fails to open
		cout << "Error opening frequency.dat" << endl;
	}
	while (!inFS.fail()) { //while file is open
		cout << left << item << " ";
		for (int i = 0; i < count; i++) { //count the number of items to display in histogram
			cout << right << "&"; 
		}
		cout << endl; //To get a new line

		inFS >> item; //take in data for next line
		inFS >> count;

		}
	inFS.close(); //Close file
	}
	

int main()
{
	int userChoice; //local menu variable


	
	while (true) { //For input validation through the loop
		menuDisplay();
		int userChoice = 0;
		cin >> userChoice;

		if (userChoice >= 1 && userChoice <= 4) { //Make sure user input is valid

			if (userChoice == 1) {
				displayEachItem();
			}
			if (userChoice == 2) {
				displaySpecificItem();
			}
			if (userChoice == 3) {
				displayHistogram();
			}
			if (userChoice == 4) {
				cout << "Okay thanks 4 using the program bye" << endl;
				break;
			}
		}
		
		
	}
		

	return 0;
}