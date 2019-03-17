/*
 * Constraint.cpp
 *
 *  Created on: Mar 16, 2019
 *      Author: ballance
 */

#include "Constraint.h"
#include "RandObjCtor.h"

namespace ccrt {

Constraint::Constraint(const std::string &name, const std::function<void ()> &func) {
	RandObjCtor &ctor = RandObjCtor::inst();

	func(); // Call the builder function to create the actual constraints

	fprintf(stdout, "Constraint: %p\n", ctor.scope());
}

Constraint::~Constraint() {
	// TODO Auto-generated destructor stub
}

} /* namespace ccrt */
