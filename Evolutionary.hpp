//
//  Evolutionary.hpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/20/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#ifndef Evolutionary_hpp
#define Evolutionary_hpp

#include <queue>

#include "Optimizer.hpp"

namespace dreal {
	class Evolutionary: public virtual Optimizer {
	public:
		virtual double optimize(const TestFunction& tf, int numIter) const;
		virtual std::string name() const;
	
	};
}
#endif /* Evolutionary_hpp */
