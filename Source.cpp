#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
/*Project 3: Corner Grocer
Beth Campbell
CS-210
Professor Eric Gregori
12/11/2022*/
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

void menuDisplay() { //Function to display main menu and get user selection
	int userSelection;
	system("Color 09"); //change font color referrence: How to print Colored text in C++ https://www.geeksforgeeks.org/how-to-print-colored-text-in-c/
	
	cout << "##############################################################################" <<endl;
	cout << "#                                 Main Menu                                  #"<<endl;
	cout << "##############################################################################" << endl;
	cout << "1. Display number of times each item was purchased" << endl;
	cout << "2. Display total amount purchased of a specific item" << endl;
	cout << "3. Display histogram of items" << endl;
	cout << "4. Exit Program" << endl;
	std::cin >> userSelection;

	while (userSelection != 1 && userSelection != 2 && userSelection != 3 && userSelection != 4) { //for invalid menu entries
		std::cin.clear();
		std::cin.ignore(256, '\n');
		system("Color C0");
		cout << "Invalid Entry. Please enter only 1, 2, 3, or 4" << endl;
		std::cin >> userSelection;
	}

	if (userSelection == 1) { //calls python-readItems to output total count
		system("CLS"); //clear screen before printing total items purchased today
		system("Color 0A"); //set color
		cout << "##############################################################################" << endl;
		cout << "#                         Total Items Purchased Today                        #" << endl;
		cout << "##############################################################################" << endl;
		CallProcedure("readItems");
	}

	else if (userSelection == 2) { //calls for intFunction TotalProductAmount 
		system("CLS"); //clears menu display
		system("Color 0D");//set color
		string userString; //declare user string
		cout << "Enter the item you wish to look up:" << endl; //prompt for input
		std::cin >> userString;
		for (int i = 0; i < userString.length(); ++i) {
			userString[i] = tolower(userString[i]); //ensures item selected is all lower case
		}
		userString[0] = toupper(userString[0]); //turns first character in item to a capital letter
		int total = callIntFunc("TotalProductAmount", userString); //gets user item frequency
		while (total < 1) {
			cout << "This item is was not sold today.";
			break;
		}
		if (total >= 1) { //print out total of items with user selection
			userString[0] = tolower(userString[0]);
			cout << total << " " << userString << " were sold today." << endl;
	}
		
	}


	else if (userSelection == 3) { // runs histogram function to output items sold
		system("CLS"); //clear screen
		system("Color 0E"); //set color
		CallProcedure("readAndWriteFile"); //output items sold with histogram
	}

	else if (userSelection == 4) { //end program option
		system("CLS"); // clear screen
		system("Color 0C"); // set color to red for exit program
		CallProcedure("ExitProgram"); //run exit function
	}
}
void main()
{
	menuDisplay(); //run menu display
	
	

}