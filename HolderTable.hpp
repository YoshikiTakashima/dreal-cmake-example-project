//
//  HolderTable.hpp
//  dreal-cmake-example-project
//
//  Created by Yoshi Takashima on 6/21/1 R.
//  Copyright © 1 Reiwa Yoshi Takashima. All rights reserved.
//

#ifndef HolderTable_hpp
#define HolderTable_hpp

#include "TestFunction.hpp"

namespace dreal {
	class HolderTable: public virtual TestFunction {
	public:
		HolderTable();
		double eval(const double x, const double y) const;
		Expression getFunction(const Variable& x, const Variable& y) const;
//		Formula getConstraint(const Variable& x, const Variable& y) const; //Same: +-10 on each axis.
		
		virtual std::string name() const;
	};
}

#endif /* HolderTable_hpp */
