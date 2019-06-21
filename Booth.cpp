//
//  Booth.cpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/20/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#include "Booth.hpp"

namespace dreal {
	Booth::Booth() {};
	
	double Booth::eval(const double x, const double y) const {
		using std::pow;
		using std::sin;
		return (pow((x + (2*y) - 7),2) + pow(((2*x) + y - 5),2));
	};
	
	Expression Booth::getFunction(const Variable& x, const Variable& y) const {
		return (pow((x + (2*y) - 7),2) + pow(((2*x) + y - 5),2));
	};
	
	std::string Booth::name() const {
		return "Booth Function";
	};
}
