/*
 * Constraint.cpp
 *
 *  Created on: Mar 16, 2019
 *      Author: ballance
 */

#include "Constraint.h"
#include "RandObjCtor.h"
#include "RandObj.h"

namespace ccrt {

Constraint::Constraint(const std::string &name, const std::function<void ()> &func) {
	m_name = name;
	m_func = func;

	RandObjCtor &ctor = RandObjCtor::inst();

	if (ctor.scope()) {
		ctor.scope()->add_constraint(this);
	} else {
		fprintf(stdout, "Error: scope is null\n");
	}
}

void Constraint::finalize() {
	RandObjCtor &ctor = RandObjCtor::inst();

	m_func(); // Call the builder function to create the actual constraints
	m_constraints = ctor.get_constraints();
	ctor.clear_constraints();

	fprintf(stdout, "Constraint: %s -- %d statements\n",
			m_name.c_str(), m_constraints.size());
}

Constraint::~Constraint() {
	// TODO Auto-generated destructor stub
}

} /* namespace ccrt */
