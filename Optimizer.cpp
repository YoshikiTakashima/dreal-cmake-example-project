//
//  Optimizer.cpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/18/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#include "Optimizer.hpp"

namespace dreal {
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
	
	double Optimizer::random(double min, double max) const {
		return (((max - min)*(((double) rand()) / ((double)RAND_MAX))) + min);
	};
};
