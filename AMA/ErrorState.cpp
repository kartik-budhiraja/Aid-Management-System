//AMA
//ErrorState.cpp
// Date	2018-03-22
// Author	Kartik Budhiraja
//This file contains the definitions of the member functions as well as the helper operators of 
//the class ErrorState under the namespace AMA


#include<iostream>
#define _CRT_SECURE_NO_WARNINGs
#include<cstring>
#include"ErrorState.h"
using namespace std;


namespace AMA {
	//constructor which initialises the object with valid data
	ErrorState::ErrorState(const char* errorMessage_input) {

		this->errorMessage = nullptr;

		if (errorMessage_input != nullptr) {
			message(errorMessage_input);
		}
	}


	//Destructor that deallocates any dynamically alloacated memory
	ErrorState::~ErrorState() {
		delete[]  errorMessage;
		errorMessage = nullptr;
	}

	//Clear any previous message and sets to safe empty state
	void ErrorState::clear() {
		delete[] errorMessage;
		errorMessage = nullptr;
	}

	//query that returns whether the object is in safe empty state or not
	bool ErrorState::isClear() const {
		return errorMessage == nullptr;
	}

	//copies the error message passed as a parameter and replace the previous message
	void ErrorState::message(const char* str) {
		clear();
		errorMessage = new char[strlen(str) + 1];
		strcpy(errorMessage, str);
		errorMessage[strlen(str)] = '\0';
	}

	//query returns the address of message stored in the object
	const char* ErrorState::message() const {
		return errorMessage;
	}

	//Helper operator to output the errormessage to the display
	std::ostream& operator<< (std::ostream& os, const ErrorState& error) {
		if (!error.isClear()) {
			const char* message = error.message();
			os << (message);
			return os;
		}
		else
			return os;

	}

}