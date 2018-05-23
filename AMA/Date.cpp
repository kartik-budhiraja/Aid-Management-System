// AMA
//FileName:Date.cpp
// Version 1.0
// Date:15 March 2018
// Author:Kartik Budhiraja
// Description:This file contains the definitions of the date class
//constructors,member functions, and the helper operator 
//overloading functions
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#include<iostream>
#include "Date.h"
using namespace std;

namespace AMA {

	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	//sets the error state variable
	void Date::errCode(int errorCode) {
		error_state = errorCode;
	}


	//Returns the error state
	int Date::errCode() const {
		return error_state;
	}


	//Default constructor setting the object to safe empty state
	Date::Date() {
		error_state = NO_ERROR;
		year = 0000;
		month = 00;
		day = 00;
		comparator = 0;
	}

	//Checks the values received and gives the values to the object accordingly
	Date::Date(int input_year, int input_month, int input_day) {
		int test = 1;
		if (!(input_year > min_year && input_year < max_year)) {
			errCode(2);
			test = 0;
		}
		if (!(test == 1 && input_month >= 1 && input_month <= 12)) {
			errCode(3);
			test = 0;
		}
		if (!(test == 1 && input_day >= 1 && input_day <= mdays(input_month, input_year))) {
			errCode(4);
		}
		if (test == 1) {
			year = input_year;
			month = input_month;
			day = input_day;
			comparator = year * 372 + month * 12 + day;
			errCode(0);
		}
		else {
			*this = Date();
		}
	}

	//for comparing the date stored in the objects
	bool Date::operator==(const Date& rhs) const {
		if (comparator != 0 && rhs.comparator != 0) {
			if (comparator == rhs.comparator)
				return true;
			else
				return false;
		}
		else
			return false;
	}

	//for comparing the date stored in the objects
	bool Date::operator!=(const Date& rhs) const {
		if (comparator != 0 && rhs.comparator != 0) {
			if (comparator != rhs.comparator)
				return true;
			else
				return false;
		}
		else
			return false;
	}

	//for comparing the date stored in the objects
	bool Date::operator<(const Date& rhs) const {
		if (comparator != 0 && rhs.comparator != 0) {
			if (comparator < rhs.comparator)
				return true;
			else
				return false;
		}
		else
			return false;
	}

	//for comparing the date stored in the objects
	bool Date::operator>(const Date& rhs) const {
		if (comparator != 0 && rhs.comparator != 0) {
			if (comparator > rhs.comparator)
				return true;
			else
				return false;
		}
		else
			return false;
	}

	//for comparing the date stored in the objects
	bool Date::operator<=(const Date& rhs) const {
		if (comparator != 0 && rhs.comparator != 0) {
			if (comparator <= rhs.comparator)
				return true;
			else
				return false;
		}
		else
			return false;
	}

	//for comparing the date stored in the objects
	bool Date::operator>=(const Date& rhs) const {
		if (comparator != 0 && rhs.comparator != 0) {
			if (comparator >= rhs.comparator)
				return true;
			else
				return false;
		}
		else
			return false;
	}


	//Returns according to the error state
	bool Date::bad() const {
		if (error_state != 0)
			return true;
		else
			return false;
	}


	//Reading the input from the console
	std::istream& Date::read(std::istream& istr) {
		bool valid = true;
		istr >> year;
		istr.ignore();
		if (!(year <= max_year &&year >= min_year)) {
			valid = false;
		}
		if (!valid) {
			*this = Date();
			errCode(2);
		}
		else {
			istr >> month;
			istr.ignore();
			if (!(month >= 1 && month <= 12)) {
				valid = false;
			}
			if (!valid) {
				*this = Date();
				errCode(3);
			}
			else {
				istr >> day;
				if (!(day >= 1 && day <= mdays(month, year))){
					*this = Date();
					errCode(4);
				}
			}
		}
		if (istr.fail()) {
			errCode(CIN_FAILED);
			return istr;
		}
		else
			return  istr;
	}


	//Writes the date to an ostream object
	std::ostream& Date::write(std::ostream& ostr) const {
		ostr.setf(ios::fixed);

		ostr << year;
		ostr << "/";
		ostr.width(2);
		ostr.fill('0');
		ostr << month;
		ostr << "/";
		ostr.width(2);
		ostr.fill('0');
		ostr << day;
		ostr.unsetf(ios::fixed);
		ostr.fill(' ');
		return ostr;
	}

	//Helper operator overloading for  output
	std::ostream& operator<<(std::ostream& ostr, const Date &d1) {
		d1.write(ostr);
		return ostr;

	}

	//Helper operator overloading for input 
	std::istream& operator>>(std::istream& istr, Date &d2) {
		d2.read(istr);
		return istr;
	}
}
