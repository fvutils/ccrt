/*
 * StmtImplies.h
 *
 *  Created on: Apr 6, 2019
 *      Author: ballance
 */

#pragma once
#include <vector>

#include "ccrt/model/IExpr.h"
#include "ccrt/model/StmtBase.h"

namespace ccrt {

class StmtImplies : public StmtBase {
public:
	StmtImplies(IExpr *e, const std::vector<IStmt *> &stmts);

	virtual ~StmtImplies();

	virtual BoolectorNode *build_constraint(Btor *btor);

protected:
	IExpr					*m_expr;
	std::vector<IStmt *>	m_stmts;

};

} /* namespace ccrt */

