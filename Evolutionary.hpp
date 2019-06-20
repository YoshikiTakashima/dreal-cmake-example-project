//
//  Evolutionary.hpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/20/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#ifndef Evolutionary_hpp
#define Evolutionary_hpp

#include <priority_queue>
#include <unordered_set>

#include "Optimizer.hpp"


namespace dreal {
	using std::pair;
	using std::priority_queue;
	using std::queue;
	
	class Evolutionary {
	public:
		virtual double optimize(const TestFunction& tf, int numIter) const;
		virtual std::string name() const;
	protected:
		std::random_device source;
		std::mt19937 generator(source());
		
		double growPopulation(queue<pair<double, double>>&wild, priority_queue<pair<double, double>>&sorted,int n);
		void selectTopP(queue<pair<double, double>>&wild, priority_queue<pair<double, double>>&sorted, double p);
	};
};

#endif /* Evolutionary_hpp */
