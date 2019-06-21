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
	
	double Annealing::optimize(const TestFunction& tf, int numIter) const {
		std::tuple<double, double, double, double> domain = tf.domain();
		double maxX = std::get<0>(domain);
		double minX = std::get<1>(domain);
		double maxY = std::get<2>(domain);
		double minY = std::get<3>(domain);
		
		double x, y, z, newX, newY, newZ, sigma,temp;
		x = this->random(minX,maxX);
		y = this->random(minY,maxY);
		temp = 1;
		const double tempDecrease = 0.99;
		
		for(int i = 0; i < numIter; i++) {
			z = tf.eval(x,y);
			newX = this->neighbor(x,(maxX - minX)/3*temp);
			newY = this->neighbor(y,(maxY - minY)/3*temp);
			newZ = tf.eval(newX, newY);
			if(probAccept(newZ, z, temp) > this->random(0,1)) {
				x = newX;
				y = newY;
				z = newZ;
			}
			temp = tempDecrease*temp;
		}
		
		return z;
	};
	
	std::string Annealing::name() const {
		return "Simulated Annealing";
	}
	
	double Annealing::neighbor(double current, double sigma) const {
		return current + (sigma*(this->stNormal()));
	};
	double Annealing::probAccept(double newCost, double oldCost, double temp) const{
		return std::exp((oldCost - newCost)/(temp));
	};
};
