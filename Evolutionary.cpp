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
		const int numEvolveRounds = 10000;
		const int initSamples = (int) 0.005 * numIter;
		
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
		
		/*Evolve top (initSamples) points*/
		const double lam = 0.85;
		const int numSamplesPerRound = 10;
		double best = points.top()();
		double sigma = std::max((maxX - minX)/ ((double) numIter), (maxY - minY)/ ((double) numIter));
		double bestX;
		double bestY;
		double bestZ;
		double currX;
		double currY;
		double currZ;
		int numSuccess;
		while(false &&!points.empty()) {
			Point pt = points.top();
			x = pt.first;
			y = pt.second;
			z = pt();
			for(int i = 0; i < numEvolveRounds; i++){
				numSuccess = 0;
				bestX = x;
				bestY = y;
				bestZ = z;
				for(int j = 0; j < numSamplesPerRound; j++) {
					currX = std::max(minX, std::min(maxX, x + (sigma*this->stNormal())));
					currY = std::max(minY, std::min(maxY, y + (sigma*this->stNormal())));
					currZ = tf.eval(currX, currY);

					if(currZ < bestZ) {
						bestX = currX;
						bestY = currY;
						bestZ = currZ;
						numSuccess++;
					}
				}
				x = bestX;
				y = bestY;
				z = bestZ;
				if(numSuccess < (numSamplesPerRound/5))
					sigma = sigma * lam;
				else
					sigma = sigma / lam;
			}
			best = std::min(best, bestZ);
			points.pop();
		}
		
		return best + 0.0001;
	};
	
	std::string Evolutionary::name() const {
		return "Evolutionary Strategy Minimization";
	}
};
