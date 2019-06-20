//
//  TestFunction.cpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/18/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#include "TestFunction.hpp"
namespace dreal {
	double TestFunction::eval(const double x, const double y) const {return x*y;};
	
	std::tuple<double,double,double,double> TestFunction::domain() const {
		return this->dom;
	};
	
	Expression TestFunction::getFunction(const Variable& x, const Variable& y) const {return x*y;};
	
	Formula TestFunction::getConstraint(const Variable& x, const Variable& y) const {
		return (x <= std::get<0>(this->dom)) &&
				(std::get<1>(this->dom) <= x) &&
				(y <= std::get<2>(this->dom)) &&
				(std::get<3>(this->dom) <= y);
	};
	
	Formula TestFunction::getConstraint(const Variable& x, const Variable& y, const double value) const {
		return ((this->getConstraint(x,y)) && ((this->getFunction(x,y)) <= value));
	};
	
	std::string TestFunction::name() const {
		return "Simple Test function: f(x,y) = x*y";
	};
	
	std::ostream& operator<< (std::ostream &out, TestFunction const& f) {
		out << f.name();
		return out;
	};
}
