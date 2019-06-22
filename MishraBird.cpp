//
//  MishraBird.cpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/21/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#include "MishraBird.hpp"

namespace dreal {
	MishraBird::MishraBird() {};
	
	double MishraBird::eval(const double x, const double y) const {
		using std::pow;
		using std::sin;
		using std::cos;
		using std::abs;
		using std::exp;
		using std::sqrt;
		return 	(sin(x)*exp(pow((1-cos(y)),2))) +
		(cos(y)*exp(pow((1-sin(x)),2))) +
		pow((x-y),2);
	};
	
	Expression MishraBird::getFunction(const Variable& x, const Variable& y) const {
		return (sin(x)*exp(pow((1-cos(y)),2))) +
		(cos(y)*exp(pow((1-sin(x)),2))) +
		pow((x-y),2);
	};
	
	std::string MishraBird::name() const {
		return "Mishra Bird";
	};
}
