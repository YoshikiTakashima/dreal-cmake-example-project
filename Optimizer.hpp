//
//  Optimizer.hpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/18/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#ifndef Optimizer_hpp
#define Optimizer_hpp

#include <stdlib.h>
#include <random>

#include "TestFunction.hpp"

namespace dreal {
	class Optimizer {
	public:
		Optimizer();
		virtual double optimize(const TestFunction& tf, int numIter) const;
		virtual std::string name() const;
		friend std::ostream& operator<< (std::ostream &out, Optimizer const& c);
	protected:
		double random(double min, double max) const;
		double stNormal() const;
		std::default_random_engine generator;
		std::normal_distribution<double> N;
		
		class Point {
		public:
			double first, second, value;
			Point(double x, double y, double value) {this->first = x; this->second = y; this->value = value;};
			bool operator<(Point other) const {return this->value < other.value;};
			double operator()() const {return this->value;};
		};
	};
};
#endif /* Optimizer_hpp */
