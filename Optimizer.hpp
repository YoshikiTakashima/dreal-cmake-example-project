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

#include "TestFunction.hpp"
//#include "TestFunction.cpp"

namespace dreal {
	class Optimizer {
	public:
		virtual double optimize(const TestFunction& tf, int numIter) const;
		virtual std::string name() const;
		friend std::ostream& operator<< (std::ostream &out, Optimizer const& c);
	protected:
		double random(double min, double max) const;
	};
};
#endif /* Optimizer_hpp */
