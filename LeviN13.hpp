//
//  LeviN13.hpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/18/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#ifndef LeviN13_hpp
#define LeviN13_hpp

#include "TestFunction.hpp"

namespace dreal {
	class LeviN13: public virtual TestFunction {
	public:
		LeviN13();
		double eval(const double x, const double y) const;
		Expression getFunction(const Variable& x, const Variable& y) const;
		Formula getConstraint(const Variable& x, const Variable& y) const;
		
		virtual std::string name() const;
	};
}

#endif /* LeviN13_hpp */
