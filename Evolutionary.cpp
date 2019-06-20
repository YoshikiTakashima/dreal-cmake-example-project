//
//  Evolutionary.cpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/20/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#include "Evolutionary.hpp"

namespace dreal {
	using std::pair;
	using std::priority_queue;
	using std::queue;
	using std::vector;
	
	double Evolutionary::optimize(const TestFunction& tf, int numIter) const {
		std::tuple<double, double, double, double> domain = tf.domain();
		double maxX = std::get<0>(domain);
		double minX = std::get<1>(domain);
		double maxY = std::get<2>(domain);
		double minY = std::get<3>(domain);
		
		const int numInitSamples = 1000;
		const int survivalMargin = 0.05;
		const double thresh = 0.2;
		const double lam = 0.85;
		double sigma = std::max((maxX - minX)/2, (maxY - minY)/2);
		
		queue<pair<double, double>> wild();
		auto cmp = [](pair<double, double> lhs, pair<double, double> rhs)
		{
			return tf.eval(lhs.first,lhs.second) < tf.eval(rhs.first,rhs.second);
		};
		std::priority_queue<int, std::vector<int>, decltype(cmp)> sorted();
		
		double x, y;
		for(int i = 0; i < numInitSamples; i++) {
			x = this->random(minX,maxX);
			y = this->random(minY,maxY);
			sorted.push(pair<double,double>(x,y));
		}
		selectTopP(wild, sorted, survivalMargin);
		
		double sucessRate;
		for(int i = 0; i < numIter; i++) {
			sucessRate = this->growPopulation(,,)
		}
		return 0; //return minimum of list.
	};
	std::string Evolutionary::name() const {
		return "Evolutionary Minimum Selection";
	}
};
