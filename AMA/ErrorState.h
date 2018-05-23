// AMA
// Version 3.3
//ErrorState.h
// Date	2018-03-22
// Author	Kartik Budhiraja
//This file contains the declarations of the class ErrorState class along with its  member functions as well as the helper operators  
// under the namespace AMA


#pragma once


namespace AMA {
	class ErrorState {
		char * errorMessage;
	public:
		//constructor which initialises the object with valid data
		explicit ErrorState(const char* errorMessage_input = nullptr);
		//deleted copy constructor
		ErrorState(const ErrorState& em) = delete;
		//deleted overloading of assignment operator
		ErrorState& operator=(const ErrorState& em) = delete;
		//Destructor that deallocates any dynamically alloacated memory
		virtual ~ErrorState();
		//Clear any previous message and sets to safe empty state
		void clear();
		//query that returns whether the object is in safe empty state or not
		bool isClear() const;
		//copies the error message passed as a parameter and replace the previous message
		void message(const char*str);
		//query returns the address of message stored in the object
		const char* message() const;
	};

	//Helper operator to output the errormessage to the display
	std::ostream& operator<<(std::ostream& os, const ErrorState &error);
}