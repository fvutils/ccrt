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
		boolector_set_opt(m_btor, BTOR_OPT_MODEL_GEN, 1);
		boolector_set_opt(m_btor, BTOR_OPT_INCREMENTAL, 1);

		fprintf(stdout, "Note: top-level variable ready to go\n");
	}

	m_seed = 1;
	m_depth = 0;
}


RandObj::RandObj(const CtorScope &scope) {
	RandObjCtor &obj_ctor = RandObjCtor::inst();

	m_seed = 1;
	m_depth = 0;

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
		boolector_set_opt(m_btor, BTOR_OPT_INCREMENTAL, 1);

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

	// TODO: need to collect constraints
	std::vector<Constraint *> constraints;
	std::vector<VarBase *> variables;
	get_constraints(constraints);
	get_variables(variables);

	// Pop previous levels
	if (m_depth > 0) {
		boolector_pop(btor(), m_depth);
		m_depth = 0;
	}

	// Push a context for just this solve
	boolector_push(btor(), 1);
	m_depth++;

	// Add collected constraints to the solver
	for (std::vector<Constraint *>::iterator it=constraints.begin();
			it!=constraints.end(); it++) {
		for (std::vector<BoolectorNode *>::const_iterator n=(*it)->constraints().begin();
				n != (*it)->constraints().end(); n++) {
			boolector_assert(btor(), *n);
		}
	}

	do_pre_randomize();


	// TODO: loop trying to find a randomize
	for (int i=0; i<1000; i++) {
		boolector_push(btor(), 1);
		m_depth++;

		BoolectorNode *sum_node = 0;
		BoolectorNode *slice = 0;

		// TODO: form a sum
		for (std::vector<VarBase *>::iterator it=variables.begin();
				it!=variables.end(); it++) {
			if ((*it)->is_rand()) {
				BoolectorNode *n = (*it)->node();
				char tmp[64];
				uint32_t coeff = (next() & 0x0FFFFFFF);

				sprintf(tmp, "%d", coeff);

				if ((*it)->bits() < 64) {
					if ((*it)->is_signed()) {
						n = boolector_sext(btor(), n, (64-(*it)->bits()));
					} else {
						n = boolector_uext(btor(), n, (64-(*it)->bits()));
					}
				}
				n = boolector_mul(btor(), n,
						boolector_constd(btor(),
								boolector_bitvec_sort(btor(), 64), tmp));

				if (sum_node) {
					sum_node = boolector_add(btor(),
							sum_node,
							n);
				} else {
					sum_node = n;
				}

				// TODO:
//				break;
			}
		}

		if (sum_node) {
			char tmp[64];
			// TODO: fix this equation a bit better
			uint32_t bits = 8;
			uint32_t seed = (next() & ((1 << bits)-1));
			sprintf(tmp, "%d", seed);

			slice = boolector_slice(btor(), sum_node, bits-1, 0);

			BoolectorNode *eq_node = boolector_eq(btor(), slice,
					boolector_constd(btor(),
							boolector_bitvec_sort(btor(), bits), tmp));

			// Extrace certain bits
			boolector_assert(btor(), eq_node);
		} else {
			fprintf(stdout, "Error: no sum_node\n");
		}

		int32_t sat = boolector_sat(m_btor);

		fprintf(stdout, "--> do_randomize\n");

		if (sat == BOOLECTOR_SAT) {
			fprintf(stdout, "SAT\n");
			ret = true;

			// Only call post-randomize if randomization succeeds
			do_post_randomize();

			break;
		} else {
			// Go back around and try again
			if (sat == BOOLECTOR_UNSAT) {
				fprintf(stdout, "UNSAT\n");
			} else {
				fprintf(stdout, "sat=%d\n", sat);
			}
		}

		boolector_pop(btor(), 1);
		m_depth--;
	}

//	boolector_pop(btor(), 1);
//	m_depth--;

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

void RandObj::get_constraints(std::vector<Constraint *> &constraints) {
	for (std::vector<Constraint *>::iterator it=m_constraints.begin();
			it!=m_constraints.end(); it++) {
		constraints.push_back(*it);
	}

	for (std::vector<IRandObj *>::iterator it=m_children.begin();
			it != m_children.end(); it++) {
		(*it)->get_constraints(constraints);
	}
}

void RandObj::get_variables(std::vector<VarBase *> &variables) {
	for (std::vector<IRandObj *>::iterator it=m_children.begin();
			it != m_children.end(); it++) {
		(*it)->get_variables(variables);
	}
}


void RandObj::add_child(IRandObj *c) {
	m_children.push_back(c);
}

void RandObj::add_variable(VarBase *var) {
	m_variables.push_back(var);
}

void RandObj::add_constraint(Constraint *c) {
	fprintf(stdout, "Note: add constraint %s with %d constraints\n",
			c->name().c_str(), c->constraints().size());

	std::vector<Constraint *>::iterator it = m_constraints.begin();

	uint32_t i=0;
	for (; i<m_constraints.size(); i++) {
		if (m_constraints.at(i)->name() == c->name()) {
			fprintf(stdout, "Note: replacing constraint\n");
			m_constraints.at(i) = c;
		}
	}

	if (i == m_constraints.size()) {
		m_constraints.push_back(c);
	}
}

void RandObj::finalize(RandObj *root) {
	for (std::vector<IRandObj *>::iterator it=m_children.begin();
			it != m_children.end(); it++) {
		(*it)->finalize(root);
	}

	// Build the resolved set of constraints in this scope
	for (std::vector<Constraint *>::iterator it=m_constraints.begin();
			it != m_constraints.end(); it++) {
		(*it)->finalize();
	}
}

uint32_t RandObj::next() {
//	m_seed ^= (m_seed << 13);
//	m_seed ^= (m_seed >> 17);
//	m_seed ^= (m_seed << 5);
	m_seed ^= (m_seed >> 12);
	m_seed ^= (m_seed << 25);
	m_seed ^= (m_seed >> 27);

	return m_seed * /*0x2545F491*/ 0x4F6CDD1D;
}

} /* namespace ccrt */
