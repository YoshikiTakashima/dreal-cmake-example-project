//
//  Annealing.cpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/21/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#include "Annealing.hpp"

namespace dreal {
	using std::priority_queue;
	using std::sort;
	
	double Evolutionary::optimize(const TestFunction& tf, int numIter) const {
		std::tuple<double, double, double, double> domain = tf.domain();
		double maxX = std::get<0>(domain);
		double minX = std::get<1>(domain);
		double maxY = std::get<2>(domain);
		double minY = std::get<3>(domain);
		
		double x, y, z, newX, newY, newZ, sigma, temp;
		sigma =
		x = this->random(minX,maxX);
		y = this->random(minY,maxY);
		z = tf.eval(x,y);
		
		for(int i = 0; i < numIter; i++) {
			
		}
		
		return z;
	};
	
	std::string Evolutionary::name() const {
		return "Simulated Annealing";
	}
	
	double Evolutionary::neighbor(double current, double sigma) const {};
	double Evolutionary::probAccept(double newCost, double oldCost) const{};
};
