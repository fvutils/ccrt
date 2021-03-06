/*
 * RandObjCtor.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */

#include "ccrt/impl/RandObjCtor.h"

#include <stdio.h>
#include "ccrt/model/VarBase.h"
#include "ccrt/model/CovergroupModel.h"

namespace ccrt {
RandObjCtor::RandObjCtor() {
	// TODO Auto-generated constructor stub

	m_covergroup = 0;
	m_coverpoint = 0;
}

RandObjCtor::~RandObjCtor() {
	// TODO Auto-generated destructor stub
}

RandObjCtor &RandObjCtor::inst() {
	if (!m_inst) {
		m_inst = new RandObjCtor();
	}
	return *m_inst;
}

std::string RandObjCtor::auto_name() {
	fprintf(stdout, "auto_name\n");
	return "foo";
}

RandObj *RandObjCtor::scope() const {
	RandObj *ret = 0;

	fprintf(stdout, "scope:\n");
	for (int i=m_scope_stack.size()-1; i>=0; i--) {
		fprintf(stdout, "  %d: %p\n", i, m_scope_stack.at(i));
		if (m_scope_stack.at(i)) {
			ret = m_scope_stack.at(i);
			break;
		}
	}
	fprintf(stdout, "  ret=%p\n", ret);

	return ret;
}

RandObj *RandObjCtor::parent() const {
	RandObj *ret = 0, *scope = 0;

	fprintf(stdout, "parent:\n");
	for (int i=m_scope_stack.size()-1; i>=0; i--) {
		fprintf(stdout, "  %d: %p\n", i, m_scope_stack.at(i));
		if (m_scope_stack.at(i)) {
			if (scope) {
				ret = m_scope_stack.at(i);
			} else {
				scope = m_scope_stack.at(i);
			}
			break;
		}
	}

	fprintf(stdout, "  ret=%p\n", ret);

	return ret;
}

void RandObjCtor::set_covergroup_ctxt(CovergroupModel *cg) {
	m_covergroup = cg;
}

void RandObjCtor::set_coverpoint_ctxt(CoverpointModel *cp) {
	m_coverpoint = cp;
}

void RandObjCtor::add_coverpoint(CoverpointModel *cp) {
	if (m_covergroup) {
		m_covergroup->add_coverpoint(cp);
	} else {
		fprintf(stdout, "Error: Constructing a coverpoint outside a covergroup\n");
	}
}

void RandObjCtor::add_crosspoint(CoverpointCrossModel *cross) {
	if (m_covergroup) {
		m_covergroup->add_crosspoint(cross);
	} else {
		fprintf(stdout, "Error: Constructing a crosspoint outside a covergroup\n");
	}
}

void RandObjCtor::add_coverpoint_bin(ICoverpointBinModel *bin) {
	if (m_coverpoint) {
		m_coverpoint->add_bin(bin);
	} else {
		fprintf(stdout, "Error: No coverpoint context set\n");
	}
}

//bool RandObjCtor::mkEq(const VarBase &lhs, const VarBase &rhs) {
//	fprintf(stdout, "mkEq: lhs=%s rhs=%s\n", lhs.name().c_str(), rhs.name().c_str());
//	return false;
//}

ConstraintBuilderExpr RandObjCtor::push_eq(
		const ConstraintBuilderExpr		&lhs,
		const ConstraintBuilderExpr		&rhs) {
//	BoolectorNode *n0, *n1;
//
//	resize(lhs, rhs, &n0, &n1);
//
//	fprintf(stdout, "--> n1\n");
//	boolector_dump_btor_node(btor(), stdout, n1);
//	fprintf(stdout, "<-- n1\n");
//
//	BoolectorNode *eq = boolector_eq(
//			btor(),
//			n0,
//			n1);
//
//	pop_constraint(lhs.node(), rhs.node());
//
//	// Equal is always unsigned and 1-bit wide
//	return ConstraintBuilderExpr(eq, 1, false);
}

ConstraintBuilderExpr RandObjCtor::push_neq(
		const ConstraintBuilderExpr		&lhs,
		const ConstraintBuilderExpr		&rhs) {
//	BoolectorNode *n0, *n1;
//
//	resize(lhs, rhs, &n0, &n1);
//
//	fprintf(stdout, "--> n0\n");
//	boolector_dump_btor_node(btor(), stdout, n0);
//	fprintf(stdout, "<-- n0\n");
//	fprintf(stdout, "--> n1\n");
//	boolector_dump_btor_node(btor(), stdout, n1);
//	fprintf(stdout, "<-- n1\n");
//
//	BoolectorNode *neq = boolector_not(btor(),
//			boolector_eq(
//					btor(),
//					n0,
//					n1));
//
//	pop_constraint(lhs.node(), rhs.node());
//
//	// Equal is always unsigned and 1-bit wide
//	return ConstraintBuilderExpr(neq, 1, false);
}

ConstraintBuilderExpr RandObjCtor::push_plus(
		const ConstraintBuilderExpr		&lhs,
		const ConstraintBuilderExpr		&rhs) {
//	BoolectorNode *n0, *n1;
//
//	resize(lhs, rhs, &n0, &n1);
//
//	BoolectorNode *plus = boolector_add(btor(), n0, n1);
//
//	pop_constraint(lhs.node(), rhs.node());
//
//	// Equal is always unsigned and 1-bit wide
//	return ConstraintBuilderExpr(plus,
//			boolector_get_width(btor(), n0),
//			false); // TODO:
}

ConstraintBuilderExpr RandObjCtor::push_minus(
		const ConstraintBuilderExpr		&lhs,
		const ConstraintBuilderExpr		&rhs) {
//	BoolectorNode *n0, *n1;
//
//	resize(lhs, rhs, &n0, &n1);
//
//	BoolectorNode *minus = boolector_sub(btor(), n0, n1);
//
//	pop_constraint(lhs.node(), rhs.node());
//
//	// Equal is always unsigned and 1-bit wide
//	return ConstraintBuilderExpr(minus,
//			boolector_get_width(btor(), n0),
//			false); // TODO:
}


ConstraintBuilderExpr RandObjCtor::push_logical_and(
		const ConstraintBuilderExpr		&lhs,
		const ConstraintBuilderExpr		&rhs) {
//	fprintf(stdout, "push_logical_and\n");
//	BoolectorNode *n0, *n1;
//
//	if (lhs.bits() == 1) {
//		n0 = lhs.node();
//	} else {
//		n0 = boolector_ne(btor(), n0,
//				boolector_zero(btor(),
//						boolector_get_sort(btor(), lhs.node())));
//	}
//
//	if (rhs.bits() == 1) {
//		n1 = rhs.node();
//	} else {
//		n1 = boolector_ne(btor(), n1,
//				boolector_zero(btor(),
//						boolector_get_sort(btor(), rhs.node())));
//	}
//
//	BoolectorNode *n_and = boolector_and(btor(), n0, n1);
//	pop_constraint(lhs.node(), rhs.node());
//
//	return ConstraintBuilderExpr(n_and, 1, false);
}

void RandObjCtor::resize(
		const ConstraintBuilderExpr		&lhs,
		const ConstraintBuilderExpr		&rhs,
		BoolectorNode 					**lhs_r,
		BoolectorNode 					**rhs_r) {
//	*lhs_r = lhs.node();
//	*rhs_r = rhs.node();
//
//	if (lhs.bits() > rhs.bits()) {
//		if (rhs.is_signed()) {
//			*rhs_r = boolector_sext(
//					btor(),
//					rhs.node(),
//					(lhs.bits()-rhs.bits()));
//		} else {
//			*rhs_r = boolector_uext(
//					btor(),
//					rhs.node(),
//					(lhs.bits()-rhs.bits()));
//		}
//	} else if (rhs.bits() > lhs.bits()) {
//		if (lhs.is_signed()) {
//			*lhs_r = boolector_sext(
//					btor(),
//					lhs.node(),
//					(rhs.bits()-lhs.bits()));
//		} else {
//			*lhs_r = boolector_uext(
//					btor(),
//					lhs.node(),
//					(rhs.bits()-lhs.bits()));
//		}
//	}
}

std::vector<IStmt *> RandObjCtor::truncate_expressions(uint32_t sz) {
	std::vector<IStmt *> ret;

	for (uint32_t i=sz; i<m_expressions.size(); i++) {
		ret.push_back(m_expressions.at(i));
	}
	m_expressions.resize(sz);

	return ret;
}

void RandObjCtor::push_constraint(BoolectorNode *c) {
	m_constraints.push_back(c);
}

void RandObjCtor::pop_constraint(BoolectorNode *c) {
	if (m_constraints.size() > 0) {
		if (m_constraints.back() != c) {
			fprintf(stdout, "Error: expecting constraint %p, but saw %p\n",
					c, m_constraints.back());
		} else {
			m_constraints.pop_back();
		}
	} else {
		fprintf(stdout, "Error: no constraints to pop\n");
	}
}

void RandObjCtor::pop_constraint(BoolectorNode *c1, BoolectorNode *c2) {
	if (m_constraints.size() >= 2) {
		if (m_constraints.back() == c1 || m_constraints.back() == c2) {
			m_constraints.pop_back();
		} else {
			fprintf(stdout, "Error(1): expecting constraint %p or %p, but saw %p\n",
					c1, c2, m_constraints.back());
		}
		if (m_constraints.back() == c1 || m_constraints.back() == c2) {
			m_constraints.pop_back();
		} else {
			fprintf(stdout, "Error(2): expecting constraint %p or %p, but saw %p\n",
					c1, c2, m_constraints.back());
		}
	} else {
		fprintf(stdout, "Error: need 2 constraints to pop, but have %d\n",
				m_constraints.size());
	}
}

void RandObjCtor::push_expr(IStmt *expr) {
	m_expressions.push_back(expr);
}

IStmt *RandObjCtor::pop_expr() {
	if (m_expressions.size() > 0) {
		IStmt *ret = m_expressions.back();
		m_expressions.pop_back();
		return ret;
	} else {
		fprintf(stdout, "Error: pop_expr() called with no expressions\n");
		return 0;
	}
}

void RandObjCtor::enter(CtorScope *scope) {
	fprintf(stdout, "--> enter %p %p\n",
			scope->typeinfo(),
			scope->scope());
	m_scope_stack.push_back(scope->scope());

}

void RandObjCtor::leave(CtorScope *scope) {
//	m_scope_stack.pop();
	if (!scope->scope()) {
		// Pop last scopes
		RandObj *last_s = m_scope_stack.at(m_scope_stack.size()-1);

		// Remove any non-null elements
		while (m_scope_stack.size() > 0 && last_s &&
				m_scope_stack.at(m_scope_stack.size()-1) && last_s) {
			m_scope_stack.pop_back();
		}
		// Remove the null element
		if (m_scope_stack.size() > 0) {
			m_scope_stack.pop_back();
		}
	}
	fprintf(stdout, "<-- leave %p %p\n",
			scope->typeinfo(),
			scope->scope());

	if (m_scope_stack.size() == 0) {
		fprintf(stdout, "Note: ready to complete RandObj construction %p\n",
				m_active_rand_obj);
		fprintf(stdout, "  %d accumulated constraints\n", m_constraints.size());
		m_active_rand_obj->finalize(m_active_rand_obj);

		// Clear out the constraints list
		m_constraints.clear();
	}
}

RandObjCtor *RandObjCtor::m_inst = 0;

}
