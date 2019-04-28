/*
 * StmtIfElse.h
 *
 *  Created on: Apr 6, 2019
 *      Author: ballance
 */
#pragma once
#include "ccrt/model/IExpr.h"
#include "ccrt/model/StmtBase.h"

namespace ccrt {

class StmtIfElse : public StmtBase {
public:
	StmtIfElse(
			IExpr			*expr,
			IStmt			*true_case
			);

	StmtIfElse(
			IExpr			*expr,
			IStmt			*true_case,
			IStmt			*false_case
			);

	virtual ~StmtIfElse();

	virtual BoolectorNode *build_constraint(Btor *btor);

	void true_case(IStmt *t) { m_true_case = t; }

	IStmt *true_case() const { return m_true_case; }

	void false_case(IStmt *f) { m_false_case = f; }

	IStmt *false_case() const { return m_false_case; }

protected:
	IExpr					*m_expr;
	IStmt					*m_true_case;
	IStmt					*m_false_case;
};

} /* namespace ccrt */

