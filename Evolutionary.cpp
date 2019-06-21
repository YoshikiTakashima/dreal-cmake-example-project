//
//  Evolutionary.cpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/20/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#include "Evolutionary.hpp"

namespace dreal {
	using std::priority_queue;
	using std::sort;
	
	double Evolutionary::optimize(const TestFunction& tf, int numIter) const {
		const int initSamples = (int) 0.05 * numIter;
		std::tuple<double, double, double, double> domain = tf.domain();
		double maxX = std::get<0>(domain);
		double minX = std::get<1>(domain);
		double maxY = std::get<2>(domain);
		double minY = std::get<3>(domain);
		
		priority_queue<Point> points;
		double x, y, z;
		for(int i = 0; i < numIter; i++) {
			x = this->random(minX,maxX);
			y = this->random(minY,maxY);
			z = tf.eval(x,y);
			if(points.size() <= initSamples)
				points.push(Point(x,y,z));
			else if(z < points.top()()) {
				points.push(Point(x,y,z));
				points.pop();
			}
		}
		
		double best = points.top()();
		while(!points.empty()) {
			Point pt = points.top();
			best = std::min(best, this->evolve(pt.first, pt.second, pt.value));
			points.pop();
		}
		
		return best;
	};
	
	double Evolutionary::evolve(double x, double y, double z) const {
		return z; //actually implement some stuff tomorrow.
	};
	
	std::string Evolutionary::name() const {
		return "Evolutionary Strategy Minimization";
	}
};
