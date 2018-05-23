// AMA
// Perishable.cpp
// Date	2018-04-13
// Author	Kartik Budhiraja
//This file contains the definitions of the class Perishable  member functions 
// under the namespace AMA


#include<iostream>
#include"Perishable.h"
using namespace std;

namespace AMA {

	//No argument constructor , sets the object to safe empty state
	Perishable::Perishable() :Product('P') {
	}

	//It stores a single file record for the current object
	std::fstream& Perishable::store(std::fstream& file, bool newLine)const {
		Product::store(file, false);
		file << ",";
		expiryDate.write(file);
		if (newLine)
			file << endl;
		return file;
	}

	//It extracts the data fields for a single file record from the fstream object
	std::fstream& Perishable::load(std::fstream& file) {
		Product::load(file);
		file.seekg(29);
		expiryDate.read(file);
		file.ignore();
		return file;
	}


	//It puts all the object data into the ostream object according to the requirement
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		os.unsetf(ios::fixed);
		Product::write(os, linear);
		if (Product::isClear()) {
			const char* test = sku();
			if (test[0] != '\0') {
				if (linear)
					expiryDate.write(os);
				else {
					os << "\n Expiry date: ";
					expiryDate.write(os);
				}
			}
		}
		return os;
	}

	//It populates the current object with the data extracted from the istream object. 
	std::istream& Perishable::read(std::istream& is) {
		Product::read(is);
		if (!is.istream::fail()) {
			Date temp;
			cout << " Expiry date (YYYY/MM/DD): ";
			temp.read(is);
			if (temp.bad()) {
				is.istream::setstate(std::ios::failbit);
				int error = temp.errCode();
				switch (error) {
				case 1:Product::message("Invalid Date Entry");
					break;
				case 2:Product::message("Invalid Year in Date Entry");
					break;
				case 3:Product::message("Invalid Month in Date Entry");
					break;
				case 4:Product::message("Invalid Day in Date Entry");
					break;
				}

			}
			else
				expiryDate = temp;
		}
		return is;
	}

	//This query returns the expiry date for the perishable product
	const Date& Perishable::expiry() const {
		return expiryDate;
	}

}