/*
 * StmtImplies.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: ballance
 */

#include "StmtImplies.h"

namespace ccrt {

StmtImplies::StmtImplies(IExpr *e, const std::vector<IStmt *> &stmts) :
		m_expr(e), m_stmts(stmts) {
	// TODO Auto-generated constructor stub

}

StmtImplies::~StmtImplies() {
	// TODO Auto-generated destructor stub
}

BoolectorNode *StmtImplies::build_constraint(Btor *btor) {
	BoolectorNode *e_n = m_expr->build_constraint(btor);

	if (m_expr->bits() > 1) {
		e_n = boolector_not(btor,
				boolector_eq(btor, e_n,
						boolector_zero(btor,
								boolector_bitvec_sort(btor, m_expr->bits())
						)
				)
		);
	}

	BoolectorNode *s_n = 0;

	// Iterate through each statement and build the boolector implementation
	for (std::vector<IStmt *>::const_iterator it=m_stmts.begin();
			it!=m_stmts.end(); it++) {
		if (s_n) {
			s_n = boolector_and(btor,
					s_n,
					(*it)->build_constraint(btor));
		} else {
			s_n = (*it)->build_constraint(btor);
		}
	}

	return boolector_implies(btor, e_n, s_n);
}

} /* namespace ccrt */
