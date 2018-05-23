// AMA
// Product.h
// Date	2018-04-07
// Author	Kartik Budhiraja
//This file contains the declarations of the class Product class along with its  member functions as well as the helper operators  
// under the namespace AMA

#pragma once
#include<iostream>
#include"iProduct.h"
#include"ErrorState.h"



#define max_sku_length 7
#define max_unit_length 10
#define max_name_length 75
#define currentTaxRate 0.13

namespace AMA {
	class Product :public iProduct {


		//Type of product
		char type;
		//Product's SKU
		char productSku[max_sku_length + 1];
		//Product's Unit
		char productUnit[max_unit_length + 1];
		//Pointer for the name of product
		char* productName;
		//Units currently on hand

		int unitsOnHand;
		//Units required
		int unitsRequired;
		//Price
		double productPrice;
		//taxable or not
		bool istaxable;
		//ErrorState Object holding the error state
		ErrorState errorState;

	protected:
		//stores the name of the product in the dynamic memory
		void name(const char*);
		//returns the address of product name string
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		//returns productPrice +  tax
		double cost() const;
		//Receives and stores the error message
		void message(const char*);
		//returns if ErrorState object is clear or not
		bool isClear() const;
	public:
		//Stores the type of the object and set it to safe empty state
		Product(char input_type = 'N');
		//Constructor initialising all the valid values to the object
		Product(const char* input_sku, const char* input_name, const char* input_unit, int input_quantityOnHand = 0, bool input_istaxable = true, double input_productPrice = 0.0, int input_quantityNeeded = 0);
		//Copy constructor 
		Product(const Product&);
		//Copy assignment operator
		Product& operator=(const Product& source);
		//Destructor of the class
		~Product();
		//Inserts data into an fstream object
		std::fstream& store(std::fstream& file, bool newline = true) const;
		//Extarcts the data from the fstream object and creates assigns the values to the current object
		std::fstream& load(std::fstream& file);
		//Inserts the data into an ostream object 
		std::ostream& write(std::ostream&os, bool linear) const;
		//Inputs the data into from the user
		std::istream& read(std::istream& is);
		//checks the passed string against the sku of the object
		bool operator==(const char*) const;
		//Returns the total cost of all items on hand along with tax
		double total_cost() const;
		//sets the units on hand to the number received
		void quantity(int);
		//Checks whether the object is in empty state or not
		bool isEmpty() const;
		//Returns the units needed
		int qtyNeeded() const;
		//Returns the units on hand
		int quantity() const;
		//Compares the SKU of the object
		bool operator>(const char*) const;
		//Compares the Name of the object
		bool operator>(const iProduct&) const;
		//Updates the units on hand
		int operator+=(int);
	};
	//Helper function to insert record into ostream
	std::ostream& operator<<(std::ostream&, const iProduct&);
	//Helper function to extract product from istream
	std::istream& operator>>(std::istream&, iProduct&);
	//Adds the total cost to the double received
	double operator+=(double&, const iProduct&);


}