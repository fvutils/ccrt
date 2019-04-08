/*
 * ConstraintStmtIfElse.h
 *
 *  Created on: Apr 6, 2019
 *      Author: ballance
 */
#pragma once
#include "ConstraintBuilderExpr.h"
#include "StmtIfElse.h"
#include <functional>

namespace ccrt {

class ConstraintStmtIfElse {
public:

	ConstraintStmtIfElse(StmtIfElse *if_else);

	ConstraintStmtIfElse(ConstraintStmtIfElse *parent);

	virtual ~ConstraintStmtIfElse();

	void else_then(const std::function<void ()> &else_case);

	ConstraintStmtIfElse else_if(
			const ConstraintBuilderExpr		&expr,
			const std::function<void ()> 	&else_case);

private:
	ConstraintStmtIfElse			*m_parent;
	StmtIfElse						*m_if_else;

};

} /* namespace ccrt */

