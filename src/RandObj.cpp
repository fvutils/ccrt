/*
 * RandObj.cpp
 *
 *  Created on: Mar 10, 2019
 *      Author: ballance
 */

#include "RandObj.h"
#include <stdio.h>

#include "impl/RandObjCtor.h"
#include "model/ExprIn.h"
#include "model/StmtBlock.h"
#include "model/StmtIfElse.h"
#include "model/VarBase.h"
#include "model/CovergroupModel.h"

namespace ccrt {

RandObj::RandObj() : m_debug(false) {
	RandObjCtor &obj_ctor = RandObjCtor::inst();

	// TODO: must decide the parent

	// TODO: if there is a parent, add this to the parent

	RandObj *parent = obj_ctor.scope();

	if (parent) {
		// Find the root
		m_parent = parent;
		m_parent->add_child(this);

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

		if (m_debug) {
			fprintf(stdout, "Note: top-level variable ready to go\n");
		}
	}

	m_seed = 1;
	m_depth = 0;
}


RandObj::RandObj(const CtorScope &scope) : m_debug(false) {
	RandObjCtor &obj_ctor = RandObjCtor::inst();

	m_seed = 1;
	m_depth = 0;

	// TODO: need to figure out exactly what the scope is
	RandObj *parent = obj_ctor.parent();
	RandObj *this_s = obj_ctor.scope();

	fprintf(stdout, "RandObj(2): %s this=%p this_s=%p parent=%p\n",
			scope.name().c_str(), this, this_s, parent);

	if (parent) {
		// Find the root
		m_parent = parent;
		m_parent->add_child(this);

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

void RandObj::set_ref(IRandObj *ref) {

	if (ref) {
		RandObj *ref_o = dynamic_cast<RandObj *>(ref);

		fprintf(stdout, "set_ref: ref=%p, ref_o=%p\n", ref, ref_o);

		if (!ref_o) {
			fprintf(stderr, "Error: failed to cast IRandObj back to RandObj\n");
		}

		std::vector<IRandObj *>::iterator t_it=m_children.begin();
		std::vector<IRandObj *>::iterator r_it=ref_o->m_children.begin();

		while (t_it != m_children.end()) {
			(*t_it)->set_ref(*r_it);

			t_it++;
			r_it++;
		}
	} else {
		// Reset the ref back to the original vaue
		for (std::vector<IRandObj *>::iterator it=m_children.begin();
				it!=m_children.end(); it++) {
			(*it)->set_ref(0);
		}
	}
}

ConstraintStmtIfElse RandObj::if_then(
		const ConstraintBuilderExpr			&expr,
		const std::function<void ()>		&true_case) {
	// Pop 'expr' off the stack
	RandObjCtor::inst().pop_expr();

	uint32_t pre_size = RandObjCtor::inst().get_expressions().size();
	// Build the constraint statements within the body. This will cause
	// the statements to be pushed onto the RandObjCtor list
	true_case();
	// Remove the newly-created statements
	std::vector<IStmt *> stmts = RandObjCtor::inst().truncate_expressions(pre_size);

	StmtIfElse *if_else = new StmtIfElse(
		expr.expr(),
		new StmtBlock(stmts)
	);

	RandObjCtor::inst().push_expr(if_else);

	return ConstraintStmtIfElse(if_else);
}

ConstraintBuilderExpr RandObj::in(
			const ConstraintBuilderExpr		&expr,
			std::initializer_list<Range>	range) {
	// Pop the 'expr' constraint off the stack
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprIn(expr.expr(), range));
}

bool RandObj::do_randomize(BoolectorNode *with) {
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

	boolector_set_opt(btor(), BTOR_OPT_SEED, next());

	// Push a context for just this solve
	boolector_push(btor(), 1);
	m_depth++;

	// Add collected constraints to the solver
	for (std::vector<Constraint *>::iterator it=constraints.begin();
			it!=constraints.end(); it++) {
		if ((*it)->constraint_mode()) {
		for (std::vector<BoolectorNode *>::const_iterator n=(*it)->constraints().begin();
				n != (*it)->constraints().end(); n++) {
			boolector_assert(btor(), *n);
		}
		}
	}

	do_pre_randomize();

	int32_t bits = -1;
	int32_t tries = 0;

	// First check to see that the system is actually valid
	int32_t sat = boolector_sat(m_btor);

	if (sat != BOOLECTOR_SAT) {
		if (m_debug) {
			fprintf(stdout, "Constraints are not satisfiable\n");
		}
		return false;
	}

	// Now, add in the randomize-with constraint if present
	if (with) {
		boolector_assert(btor(), with);

		int32_t sat = boolector_sat(m_btor);

		if (sat != BOOLECTOR_SAT) {
			if (m_debug) {
				fprintf(stdout, "Constraints added by 'with' are not satisfiable\n");
			}
			return false;
		}
	}

	// TODO: loop trying to find a randomize
	for (int i=0; i<10000; i++) {
		boolector_push(btor(), 1);
		m_depth++;
		tries++;

		BoolectorNode *sum_node = 0;
		BoolectorNode *slice = 0;

		uint32_t total_bits = 0;

		if (bits != 0) {
		for (std::vector<VarBase *>::iterator it=variables.begin();
				it!=variables.end(); it++) {
			if ((*it)->is_rand()) {
				char tmp[65];
				BoolectorNode *n = (*it)->node();

//				uint64_t coeff = (next() & 0xFFFFFFFF);
				uint64_t coeff = next();

				for (uint32_t j=0; j<64; j++) {
					tmp[64-j-1] = (coeff & (j<<i))?'1':'0';
				}
				tmp[64] = 0;

				total_bits += (*it)->bits();

				if ((*it)->bits() < 64) {
					if ((*it)->is_signed()) {
						n = boolector_sext(btor(), n, (64-(*it)->bits()));
					} else {
						n = boolector_uext(btor(), n, (64-(*it)->bits()));
					}
				}
				n = boolector_mul(btor(), n,
						boolector_const(btor(), tmp));

				if (sum_node) {
					sum_node = boolector_add(btor(),
							sum_node,
							n);
				} else {
					sum_node = n;
				}
			}
		}
		}

		if (bits == -1) {
			// Initialize based on total_bits
			if (total_bits > 10) {
				bits = 10;
			} else if (total_bits > 2) {
				bits = total_bits / 4;
			} else {
				bits = 1;
			}
		}

		if (sum_node) {
			char tmp[65];
			// TODO: fix this equation a bit better
			uint32_t seed = (next() & ((1 << bits)-1));
//			uint32_t base = (next() % 16);
			uint32_t base = 0;

			for (uint32_t j=0; j<bits; j++) {
				tmp[bits-j-1] = (seed & (1<<j))?'1':'0';
			}
			tmp[bits] = 0;

			slice = boolector_slice(btor(), sum_node, bits+base-1, base);

			BoolectorNode *eq_node = boolector_eq(btor(), slice,
					boolector_const(btor(), tmp));

			// Extrace certain bits
			boolector_assert(btor(), eq_node);
		}

		boolector_simplify(btor());

		int32_t sat = boolector_sat(m_btor);

		if (sat == BOOLECTOR_SAT) {
			if (m_debug) {
				fprintf(stdout, "SAT\n");
			}
			ret = true;

			// Only call post-randomize if randomization succeeds
			do_post_randomize();

			break;
		} else {
			// Go back around and try again, but with fewer rand bits
			if (bits > 1) {
				bits--;
			}
		}

		boolector_pop(btor(), 1);
		m_depth--;
	}

	if (ret) {
		if (tries > 1 && m_debug) {
			fprintf(stdout, "SAT after %d tries\n", tries);
		}
	} else {
		// Go back to the original non-rand result
		if (m_debug) {
			fprintf(stdout, "Warning: UNSAT after %d tries\n", tries);
		}
		boolector_sat(m_btor);
		ret = true;
	}

//	boolector_pop(btor(), 1);
//	m_depth--;

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
