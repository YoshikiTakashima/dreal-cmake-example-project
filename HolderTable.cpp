//
//  HolderTable.cpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/21/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#include "HolderTable.hpp"

#define _USE_MATH_DEFINES

namespace dreal {
	HolderTable::HolderTable() {};
	
	double HolderTable::eval(const double x, const double y) const {
		using std::pow;
		using std::sin;
		using std::cos;
		using std::abs;
		using std::exp;
		using std::sqrt;
		return -1*abs(sin(x)*cos(y)*exp(abs(1 - (sqrt(pow(x,2)+pow(y,2))/M_PI))));
	};
	
	Expression HolderTable::getFunction(const Variable& x, const Variable& y) const {
		return (-1*abs(sin(x)*cos(y)*exp(abs(1 - (sqrt(pow(x,2)+pow(y,2))/M_PI)))));
	};
	
	std::string HolderTable::name() const {
		return "Holder Table 2D";
	};
}
