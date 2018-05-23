//AMA
//FileName:Date.h
// Version 1.0
// Date:15 March 2018
// Author:Kartik Budhiraja
// Description:This file contains the declaration of the date class
//along with its data members as well as the
//member functions, and the helper operator 
//overloading functions
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////


#include<iostream>
#ifndef AMA_DATE_H
#define AMA_DATE_H



//Macros for the states of errors
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4

namespace AMA {
	const int min_year = 2000;
	const int max_year = 2030;


	class Date {
		int year;
		int month;
		int day;
		int comparator;
		int error_state;

		// number of days in month mon_ and year year_
		int mdays(int, int)const;


		//sets the error state variable
		void errCode(int errorCode);

	public:

		//Initializes the object to safe empty state
		Date();


		//Checks the values received and gives the values to the object accordingly
		Date(int, int, int);

		//for comparing the date stored in the objects
		bool operator==(const Date& rhs) const;

		//for comparing the date stored in the objects
		bool operator!=(const Date& rhs) const;

		//for comparing the date stored in the objects
		bool operator<(const Date& rhs) const;

		//for comparing the date stored in the objects
		bool operator>(const Date& rhs) const;

		//for comparing the date stored in the objects
		bool operator<=(const Date& rhs) const;

		//for comparing the date stored in the objects
		bool operator>=(const Date& rhs) const;

		//Returns the error state
		int errCode() const;

		//Returns according to the error state
		bool bad() const;

		//Reading the input from the console
		std::istream& read(std::istream& istr);

		//Writes the date to an ostream object
		std::ostream& write(std::ostream& ostr) const;

	};

	//Helper operator overloading for  output
	std::ostream& operator<<(std::ostream&, const Date&);


	//Helper operator overloading for input
	std::istream& operator>>(std::istream&, Date&);


}
#endif