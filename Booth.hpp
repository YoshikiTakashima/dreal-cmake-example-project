//
//  Booth.hpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/20/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#ifndef Booth_hpp
#define Booth_hpp

#include "TestFunction.hpp"

namespace dreal {
	class Booth: public virtual TestFunction {
	public:
		Booth();
		double eval(const double x, const double y) const;
		Expression getFunction(const Variable& x, const Variable& y) const;
		Formula getConstraint(const Variable& x, const Variable& y) const;
		
		virtual std::string name() const;
	};
}

#endif /* Booth_hpp */
