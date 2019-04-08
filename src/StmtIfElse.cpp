/*
 * StmtIfElse.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: ballance
 */

#include "StmtIfElse.h"

namespace ccrt {

StmtIfElse::StmtIfElse(
		IExpr			*expr,
		IStmt			*true_case) {
	m_expr = expr;
	m_true_case = true_case;
	m_false_case = 0;
}

StmtIfElse::StmtIfElse(
		IExpr			*expr,
		IStmt			*true_case,
		IStmt			*false_case) {
	m_expr = expr;
	m_true_case = true_case;
	m_false_case = false_case;
}

StmtIfElse::~StmtIfElse() {
	// TODO Auto-generated destructor stub
}

BoolectorNode *StmtIfElse::build_constraint(Btor *btor) {
	BoolectorNode *ret = 0;

	if (m_false_case) {
		// True if-then-else
		ret = boolector_cond(
				btor,
				m_expr->build_constraint(btor),
				m_true_case->build_constraint(btor),
				m_false_case->build_constraint(btor)
				);
	} else {
		// Just if-then
		ret = boolector_implies(
				btor,
				m_expr->build_constraint(btor),
				m_true_case->build_constraint(btor)
				);
	}

	return ret;
}

} /* namespace ccrt */
