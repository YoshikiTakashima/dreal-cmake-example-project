//
//  Optimizer.cpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/18/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#include "Optimizer.hpp"

#define _USE_MATH_DEFINES
namespace dreal {
	Optimizer::Optimizer() {
	};
	
	double Optimizer::optimize(const TestFunction& tf, int numIter) const {
		std::tuple<double, double, double, double> domain = tf.domain();
		double maxX = std::get<0>(domain);
		double minX = std::get<1>(domain);
		double maxY = std::get<2>(domain);
		double minY = std::get<3>(domain);
		
		double best = tf.eval(this->random(minX,maxX),this->random(minY,maxY));
		double x, y;
		for(int i = 0; i < numIter; i++) {
			x = this->random(minX,maxX);
			y = this->random(minY,maxY);
			best = std::min(best, tf.eval(x,y));
		}
		return best;
	};
	std::string Optimizer::name() const {
		return "Uniform Random Minimization";
	};
	
	std::ostream& operator<< (std::ostream &out, Optimizer const& c) {
		out << c.name();
		return out;
	};
	
	double Optimizer::random(double min, double max) const {
		double r = std::max(1, std::min(rand(),RAND_MAX-1)); // make it exlcusive of endpoints.
		return (((max - min)*(r / ((double) RAND_MAX))) + min);
	};
	
	double Optimizer:: stNormal() const {
		double u1 = this->random(0,1);
		double u2 = this->random(0,1);
		return std::sqrt(-2*std::log(u1))*std::cos(2*M_PI*u2);
	};
};
