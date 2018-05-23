// AMA
// Product.cpp
// Date	2018-04-07
// Author	Kartik Budhiraja
//This file contains the definitions of the class Product  member functions as well as the helper operators  
// under the namespace AMA

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<cstring>
#include<fstream>
#include"Product.h"
using namespace std;



namespace AMA {

	//stores the name of the product in the dynamic memory
	void Product::name(const char* input_name) {
		productName = nullptr;
		if (input_name != nullptr) {
			productName = new char[strlen(input_name) + 1];
			strncpy(productName, input_name, strlen(input_name));
			productName[strlen(input_name)] = '\0';
		}
		else {
			delete[] productName;
			productName = nullptr;
		}
	}


	//returns the address of product name string
	const char* Product::name() const {
		if (productName == nullptr)
			return nullptr;
		else
			return productName;
	}

	//returns the address of product sku string
	const char* Product::sku()	const {
		return productSku;
	}

	//returns the address of product unit string
	const char* Product::unit() const {
		return productUnit;
	}

	//returns whether the product is taxed or not
	bool Product::taxed() const {
		return istaxable;
	}

	//returns the price of the product 
	double Product::price() const {
		return productPrice;
	}

	//returns productPrice +  tax
	double Product::cost() const {
		if (istaxable)
			return (productPrice + (productPrice*currentTaxRate));
		else
			return productPrice;
	}


	//Receives and stores the error message
	void Product::message(const char* input_error) {
		errorState.ErrorState::message(input_error);
	}

	//returns if ErrorState object is clear or not
	bool Product::isClear() const {
		return errorState.ErrorState::isClear();
	}


	//Stores the type of the object and set it to safe empty state
	Product::Product(char input_type) {
		type = input_type;
		//Safe empty state
		productSku[0] = '\0';
		productUnit[0] = '\0';
		productName = nullptr;
		unitsOnHand = 0;
		unitsRequired = 0;
		productPrice = 0;
		istaxable = false;
	}


	//Constructor initialising all the valid values to the object
	Product::Product(const char* input_sku, const char* input_name, const char* input_unit, int input_quantityOnHand, bool input_istaxable, double input_productPrice, int input_quantityNeeded) {
		strncpy(productSku, input_sku, strlen(input_sku));
		productSku[strlen(input_sku)] = '\0';
		name(input_name);
		strncpy(productUnit, input_unit, strlen(input_unit));
		productUnit[strlen(input_unit)] = '\0';
		unitsOnHand = input_quantityOnHand;
		unitsRequired = input_quantityNeeded;
		istaxable = input_istaxable;
		productPrice = input_productPrice;
	}




	//Copy Constructor
	Product::Product(const Product& objToCopyFrom) {
		productName = nullptr;
		*this = objToCopyFrom;
	}


	//Copy assignment operator
	Product& Product::operator=(const Product& source) {
		//Checking for self assignment
		if (this != &source) {
			name(source.productName);
			strncpy(productSku, source.productSku, strlen(source.productSku));
			productSku[strlen(source.productSku)] = '\0';
			strncpy(productUnit, source.productUnit, strlen(source.productUnit));
			productUnit[strlen(source.productUnit)] = '\0';
			unitsOnHand = source.unitsOnHand;
			unitsRequired = source.unitsRequired;
			istaxable = source.istaxable;
			productPrice = source.productPrice;
		}
		return *this;

	}

	//Destructor
	Product::~Product() {
		delete[] productName;
		productName = nullptr;

	}

	//Inserts data into an fstream object
	std::fstream& Product::store(std::fstream& file, bool newline) const {
		file << type << ",";
		file << productSku << "," << productName << "," << productUnit << "," << istaxable << "," << productPrice << "," << unitsOnHand << "," << unitsRequired;
		if (newline)
			file << endl;
		return file;
	}


	//Extarcts the data from the fstream object and creates assigns the values to the current object
	std::fstream& Product::load(std::fstream& file) {

		//extracted Product's SKU
		char extractedSku[max_sku_length + 1];
		//extracted Product's Unit
		char extractedProductUnit[max_unit_length + 1];
		//extracted Pointer for the name of product
		char extractedProductName[max_name_length + 1];
		//extracted Units currently on hand
		int extractedUnitsOnHand;
		//extracted Units required
		int extractedUnitsRequired;
		//extracted Price
		double extractedPrice;
		//extracted taxable or not
		bool extractedIstaxable;


		file.get(extractedSku, max_sku_length, ',');
		file.ignore();
		file.get(extractedProductName, max_name_length, ',');
		file.ignore();
		file.get(extractedProductUnit, max_unit_length, ',');
		file.ignore();
		file >> extractedIstaxable;
		file.ignore();
		file >> extractedPrice;
		file.ignore();
		file >> extractedUnitsOnHand;
		file.ignore();
		file >> extractedUnitsRequired;

		Product temp(extractedSku, extractedProductName, extractedProductUnit, extractedUnitsOnHand, extractedIstaxable, extractedPrice, extractedUnitsRequired);

		*this = temp;

		return file;
	}


	//Inserts the data into an ostream object 
	std::ostream& Product::write(std::ostream&os, bool linear) const {
		if (errorState.isClear()) {
			os.unsetf(ios::fixed);
			if (linear) {
				os.setf(ios::left);
				os.width(max_sku_length);
				os << productSku;
				os << "|";
				os.width(20);
				os << productName;
				os << "|";
				os.unsetf(ios::left);
				os.setf(ios::fixed);
				os.precision(2);
				os.width(7);
				os << cost();
				os << "|";
				os.width(4);
				os << unitsOnHand;
				os << "|";
				os.width(10);
				os.setf(ios::left);
				os << productUnit;
				os << "|";
				os.unsetf(ios::left);
				os.width(4);
				os << unitsRequired << "|";
				os.unsetf(ios::fixed);
			}
			else {
				os.setf(ios::fixed);
				os << " Sku: " << productSku << endl;
				os << " Name (no spaces): " << productName << endl;
				os << " Price: " << productPrice << endl;
				if (istaxable)
					os << " Price after tax: " << cost() << endl;
				else
					os << " Price after tax: N/A" << endl;
				os << " Quantity on Hand: " << unitsOnHand << " " << productUnit << endl;
				os << " Quantity needed: " << unitsRequired;
			}
		}
		else {
			os << errorState.message();
		}
		return os;
	}


	//Inputs the data into from the user
	std::istream& Product::read(std::istream& is) {

		char input_name[max_name_length + 1];
		char input_sku[max_sku_length + 1];
		char input_unit[max_unit_length + 1];
		bool valid = true;
		bool input_tax;
		char test;
		double input_price;
		int input_qtyhand, input_qtyneeded;

		cout << " Sku: ";
		is >> input_sku;
		cout << " Name (no spaces): ";
		is >> input_name;
		cout << " Unit: ";
		is >> input_unit;

		cout << " Taxed? (y/n): ";
		is >> test;
		if (test != 'y' && test != 'Y' && test != 'n' && test != 'N') {
			is.setstate(std::ios::failbit); //if tax option fails
			message("Only (Y)es or (N)o are acceptable");
			valid = false;
		}
		else if (test == 'y' || test == 'Y') {
			input_tax = true;
		}
		else {
			input_tax = false;
		}

		if (valid) {
			cout << " Price: ";
			is >> input_price;
			if (is.fail()) {
				is.istream::setstate(std::ios::failbit);
				message("Invalid Price Entry");
				valid = false;
			}
		}

		if (valid) {
			cout << " Quantity on hand: ";
			is >> input_qtyhand;
			if (is.fail())
			{
				is.istream::setstate(std::ios::failbit);
				message("Invalid Quantity Entry");
				valid = false;
			}
		}

		if (valid) {
			cout << " Quantity needed: ";
			is >> input_qtyneeded;
			is.ignore();
			if (is.fail())
			{
				is.istream::setstate(std::ios::failbit);
				message("Invalid Quantity Needed Entry");
				valid = false;
			}
		}



		if (valid) { //all inputs are successful, create temp object and assign current object to it
			Product temp(input_sku, input_name, input_unit, input_qtyhand, input_tax, input_price, input_qtyneeded);

			*this = temp;
			errorState.clear();
		}

		return is;


	}


	//checks the passed string against the sku of the object
	bool Product::operator==(const char* skuToCheck) const {
		return !(strcmp(productSku, skuToCheck));
	}


	//Returns the total cost of all items on hand along with tax
	double Product::total_cost() const {
		return (unitsOnHand*cost());
	}


	//sets the units on hand to the number received
	void Product::quantity(int inputUnitsOnHand) {
		if (inputUnitsOnHand > 0)
			unitsOnHand = inputUnitsOnHand;
	}


	//Checks whether the object is in empty state or not
	bool Product::isEmpty() const {
		return productName == nullptr && productPrice == 0;
	}


	//Returns the units needed
	int Product::qtyNeeded() const {
		return unitsRequired;
	}

	//Returns the units on hand
	int Product::quantity() const {
		return unitsOnHand;
	}

	//Compares the SKU of the object
	bool Product::operator>(const char* skuToCompare) const {
		return (strcmp(productSku, skuToCompare) > 0);
	}

	//Compares the Name of the object
	bool Product::operator>(const iProduct& nameToCompare) const {
		const char* storedName = name();
		return (strcmp(name(), storedName) > 0);
	}

	// Updates the units on hand
	int Product::operator+=(int quantityToAdd) {
		if (quantityToAdd > 0) {
			unitsOnHand += quantityToAdd;
		}
		return unitsOnHand;
	}

	//Helper function to insert record into ostream
	std::ostream& operator<<(std::ostream& os, const iProduct& sample) {
		sample.write(os, true);
		return os;
	}

	//Helper function to extract product from istream
	std::istream& operator>>(std::istream& is, iProduct& sample) {
		sample.read(is);
		return is;
	}


	//Adds the total cost to the double received
	//overloaded operator +=, adds total cost and double received and returns it
	double operator+=(double& d, const iProduct& p) {
		d += p.total_cost();
		return d;
	}


}