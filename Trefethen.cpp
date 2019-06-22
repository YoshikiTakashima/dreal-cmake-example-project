//
//  Trefethen.cpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/21/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#include "Trefethen.hpp"

namespace dreal {
	Trefethen::Trefethen() {};
	
	double Trefethen::eval(const double x, const double y) const {
		using std::pow;
		using std::sin;
		using std::cos;
		using std::abs;
		using std::exp;
		using std::sqrt;
		return 	(0.25*pow(x,2)) +
		(0.25*pow(y,2)) +
		(exp(sin(50*x))) -
		(sin((10*x)+(10*x))) +
		(sin(60*exp(y))) +
		(sin(70*sin(x))) +
		(sin(sin(80*y)));
	};
	
	Expression Trefethen::getFunction(const Variable& x, const Variable& y) const {
		return (0.25*pow(x,2)) +
		(0.25*pow(y,2)) +
		(exp(sin(50*x))) -
		(sin((10*x)+(10*x))) +
		(sin(60*exp(y))) +
		(sin(70*sin(x))) +
		(sin(sin(80*y)));
	};
	
	std::string Trefethen::name() const {
		return "Trefethen Function";
	};
}
