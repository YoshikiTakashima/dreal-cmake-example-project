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
		
		
		
		const double tempDecrease = 0.99;
		const double smallEnough =0.00001;
		int itersUntilConvergence = std::ceil(std::log(smallEnough) / std::log(tempDecrease));
		
		double x, y, z, newX, newY, newZ,temp;
		x = this->random(minX,maxX);
		y = this->random(minY,maxY);
		z = tf.eval(x,y);
		double best = z;
		
		for(int j = 0; j < std::max(1, numIter / itersUntilConvergence); j++) {
			temp = 1;
			for(int i = 0; i < itersUntilConvergence; i++) {
				z = tf.eval(x,y);
				newX = std::max(minX, std::min(this->neighbor(x,(maxX - minX)/2*temp),maxX));
				newY = std::max(minY, std::min(this->neighbor(y,(maxY - minY)/2*temp),maxY));
				newZ = tf.eval(newX, newY);
				if(probAccept(newZ, z, temp) > this->random(0,1)) {
					x = newX;
					y = newY;
					z = newZ;
				}
				temp = tempDecrease*temp;
			}
			x = this->random(minX,maxX);
			y = this->random(minY,maxY);
			if (z < best) {
				best = z;
			}
		}
		
		return best;
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
