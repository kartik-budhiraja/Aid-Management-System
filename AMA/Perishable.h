// AMA
// Perishable.h
// Date	2018-04-13
// Author	Kartik Budhiraja
//This file contains the declarations of the class Perishable class along with its  member functions 
// under the namespace AMA


#pragma once
#include"Product.h"
#include"Date.h"

namespace AMA {
	class Perishable :public Product {
		Date expiryDate;
	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};




}
