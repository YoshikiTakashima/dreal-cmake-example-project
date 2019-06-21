//
//  Annealing.hpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/21/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#ifndef Annealing_hpp
#define Annealing_hpp

#include "Optimizer.hpp"

namespace dreal {
	class Annealing: public virtual Optimizer {
	public:
		virtual double optimize(const TestFunction& tf, int numIter) const;
		virtual std::string name() const;
	protected:
		double neighbor(double current, double sigma) const;
		double probAccept(double newCost, double oldCost,double temp) const;
	};
}

#endif /* Annealing_hpp */
