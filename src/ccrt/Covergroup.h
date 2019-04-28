/*
 * Covergroup.h
 *
 *  Created on: Apr 10, 2019
 *      Author: ballance
 */
#pragma once
#include "ccrt/impl/CovergroupObj.h"
#include "ccrt/impl/CtorScope.h"
#include "RandObj.h"
#include <functional>
#include "ccrt/impl/ConstraintBuilderExpr.h"

namespace ccrt {


template <class T> class Covergroup : public CovergroupObj, public T {
public:

	// Constructor for an inline covergroup
	Covergroup(const CtorScope &scope, std::function<void ()> &func);


	// Samples the covergroup using the definition object
	void sample() {
		do_sample(0);
	}

	void sample(T &it) {
		do_sample(&it);
	}

	void sample(T *it) {
		do_sample(it);
	}

protected:

	// Only extending classes can use this constructor
	Covergroup(const CtorScope &scope) : CovergroupObj(this), T((RandObj *)0) {
		// TODO: set RandObj reference on the CovergroupObj
	}

private:

};

//class MyRandClass : public RandObj {
//public:
//	int				i;
//
//};

// Want an inline covergroup
//Covergroup<MyRandClass> cg { "cg", [this] {
//	Coverpoint cp {"cp", t.i, [this] {
//	}
//	};
//}
//};
}
