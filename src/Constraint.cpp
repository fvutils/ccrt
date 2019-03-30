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
	m_constraint_mode = true;

	RandObjCtor &ctor = RandObjCtor::inst();

	if (ctor.scope()) {
		ctor.scope()->add_constraint(this);
	} else {
		fprintf(stdout, "Error: scope is null\n");
	}
}

void Constraint::finalize() {
	RandObjCtor &ctor = RandObjCtor::inst();

	ctor.clear_expr();
	m_func(); // Call the builder function to create the actual constraints
	const std::vector<IExpr *> &expr = ctor.get_expressions();
	for (std::vector<IExpr *>::const_iterator it=expr.begin();
			it!=expr.end(); it++) {
		BoolectorNode *c = (*it)->build_constraint(ctor.btor());
		fprintf(stdout, "Constraint: %p\n", c);
		m_constraints.push_back(c);
	}
	ctor.clear_expr();

	fprintf(stdout, "Constraint: %s -- %d statements\n",
			m_name.c_str(), m_constraints.size());
}

Constraint::~Constraint() {
	// TODO Auto-generated destructor stub
}

void Constraint::constraint_mode(bool mode) {
	m_constraint_mode = mode;
}

} /* namespace ccrt */
