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

		fprintf(stdout, "Note: top-level variable ready to go\n");
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

		// Let the constructor object know that we are active
		obj_ctor.set_active_rand_obj(this);
	}
}

RandObj::~RandObj() {
	if (!m_parent) {
		boolector_release_all(m_btor);
	}
	// TODO Auto-generated destructor stub
}

std::string RandObj::toString() {
	std::string ret;

	for (std::vector<IRandObj *>::iterator it=m_children.begin();
			it != m_children.end(); it++) {
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
	bool ret = false;
	if (m_parent) {
		// Can only randomize a root field
		return false;
	}

	do_pre_randomize();

	int32_t sat = boolector_sat(m_btor);

	fprintf(stdout, "--> do_randomize\n");

	if (sat == BOOLECTOR_SAT) {
		fprintf(stdout, "SAT\n");
		ret = true;

		// Only call post-randomize if randomization succeeds
		do_post_randomize();
	} else {
		if (sat == BOOLECTOR_UNSAT) {
			fprintf(stdout, "UNSAT\n");
		} else {
			fprintf(stdout, "sat=%d\n", sat);
		}
	}

	fprintf(stdout, "<-- do_randomize\n");


	return ret;
}

void RandObj::do_pre_randomize() {
	pre_randomize();
	for (std::vector<IRandObj *>::iterator it=m_children.begin();
			it != m_children.end(); it++) {
		(*it)->do_pre_randomize();
	}
}

void RandObj::do_post_randomize() {
	post_randomize();

	for (std::vector<IRandObj *>::iterator it=m_children.begin();
			it != m_children.end(); it++) {
		(*it)->do_post_randomize();
	}
}

void RandObj::add_child(IRandObj *c) {
	m_children.push_back(c);
}

void RandObj::add_variable(VarBase *var) {
	m_variables.push_back(var);
}

void RandObj::add_constraint(Constraint *c) {
	m_constraints.push_back(c);
}

void RandObj::finalize(RandObj *root) {
	for (std::vector<IRandObj *>::iterator it=m_children.begin();
			it != m_children.end(); it++) {
		(*it)->finalize(root);
	}
}

} /* namespace ccrt */
