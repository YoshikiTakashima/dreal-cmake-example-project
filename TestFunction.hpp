//
//  TestFunction.hpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/18/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//
// 	Template for All other test functions.

#ifndef TestFunction_hpp
#define TestFunction_hpp

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <tuple>
#include <numeric>
#include <chrono>

#include "dreal/dreal.h"

namespace dreal {
	class TestFunction {
	public:
		virtual double eval(const double x, const double y) const;
		std::tuple<double,double,double,double> domain() const; //x, -x, y, -y, in that order
		virtual Expression getFunction(const Variable& x, const Variable& y) const;
		virtual Formula getConstraint(const Variable& x, const Variable& y) const;
		Formula getConstraint(const Variable& x, const Variable& y, const double value) const;
		
		virtual std::string name() const;
		friend std::ostream& operator<< (std::ostream &out, TestFunction const& f);
		
	protected:
		const std::tuple<double,double,double,double> dom = std::make_tuple(10, -10, 10, -10);
	};
}

#endif /* TestFunction_hpp */
