//
//  LeviN13.cpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/18/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#include "LeviN13.hpp"

namespace dreal {
	LeviN13::LeviN13() {};
	
	double LeviN13::eval(const double x, const double y) const {
		using std::pow;
		using std::sin;
		return (pow(sin(3 * 3.141592 * x),2) +
				(pow(x - 1,2)) * (1 + pow(sin(3 * 3.141592 * y),2)) +
				(pow(y - 1,2)) * (1 + pow(sin(2 * 3.141592 * y),2)));
	};
	
	Expression LeviN13::getFunction(const Variable& x, const Variable& y) const {
		return (pow(sin(3 * 3.141592 * x),2) +
				(pow(x - 1,2)) * (1 + pow(sin(3 * 3.141592 * y),2)) +
				(pow(y - 1,2)) * (1 + pow(sin(2 * 3.141592 * y),2)));
	};
	Formula LeviN13::getConstraint(const Variable& x, const Variable& y) const {
		return ((-10 <= x) && (x <= 10) && (-10 <= y) && (y <= 10));
	};
	
	std::string LeviN13::name() const {
		return "Levi N.13";
	};
}
