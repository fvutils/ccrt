/*
 * RandObj.cpp
 *
 *  Created on: Mar 10, 2019
 *      Author: ballance
 */

#include "RandObj.h"
#include "RandObjCtor.h"
#include "VarBase.h"
#include <stdio.h>

namespace ccrt {

RandObj::RandObj() {
	RandObjCtor &obj_ctor = RandObjCtor::inst();

	// TODO: must decide the parent

	// TODO: if there is a parent, add this to the parent

	RandObj *parent = obj_ctor.scope();
	fprintf(stdout, "RandObj: this=%p parent=%p\n", this, parent);

	if (parent) {
		// Find the root
		m_parent = parent;

		while (parent->m_parent) {
			parent = parent->m_parent;
		}

		m_btor = parent->m_btor;
	} else {
		// Create a btor for ourselves
		m_parent = 0;

		m_btor = boolector_new();
	}
}

RandObj::RandObj(const CtorScope &scope) {
	RandObjCtor &obj_ctor = RandObjCtor::inst();

	// TODO: need to figure out exactly what the scope is
	RandObj *parent = obj_ctor.parent();

	if (parent) {
		// Find the root
		m_parent = parent;

		while (parent->m_parent) {
			parent = parent->m_parent;
		}

		m_btor = parent->m_btor;
	} else {
		// Create a btor for ourselves
		m_parent = 0;

		m_btor = boolector_new();
		boolector_set_opt(m_btor, BTOR_OPT_MODEL_GEN, 1);
	}
	fprintf(stdout, "RandObj: this=%p parent=%p\n", this, parent);

}

RandObj::~RandObj() {
	if (!m_parent) {
		boolector_release_all(m_btor);
	}
	// TODO Auto-generated destructor stub
}

std::string RandObj::toString() {
	std::string ret;

	for (std::vector<VarBase *>::iterator it=m_fields.begin();
			it != m_fields.end(); it++) {
		ret += (*it)->toString() + "\n";
	}

	return ret;
}

void RandObj::pre_randomize() {
}

void RandObj::post_randomize() {
	// Do Nothing
}

bool RandObj::do_randomize() {
	if (m_parent) {
		// Can only randomize a root field
		return false;
	}

	int32_t sat = boolector_sat(m_btor);

	fprintf(stdout, "--> do_randomize\n");

	if (sat == BOOLECTOR_SAT) {
		fprintf(stdout, "SAT\n");
	} else if (sat == BOOLECTOR_UNSAT) {
		fprintf(stdout, "UNSAT\n");
	} else {
		fprintf(stdout, "sat=%d\n", sat);
	}

	fprintf(stdout, "<-- do_randomize\n");

	return true;
}

void RandObj::add_field(VarBase *f) {
	m_fields.push_back(f);
}

void RandObj::add_child(RandObj *c) {
	// TODO
}

} /* namespace ccrt */
