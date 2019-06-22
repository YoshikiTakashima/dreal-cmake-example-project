//
//  MishraBird.hpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/21/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#ifndef MishraBird_hpp
#define MishraBird_hpp

#include "TestFunction.hpp"

namespace dreal {
	class MishraBird: public virtual TestFunction {
	public:
		MishraBird();
		double eval(const double x, const double y) const;
		Expression getFunction(const Variable& x, const Variable& y) const;
		
		virtual std::string name() const;
	};
}

#endif /* MishraBird_hpp */
