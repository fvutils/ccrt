/*
 * ConstraintStmtIfElse.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: ballance
 */

#include "ccrt/impl/ConstraintStmtIfElse.h"

#include "ccrt/model/StmtBlock.h"
#include "RandObjCtor.h"

namespace ccrt {

ConstraintStmtIfElse::ConstraintStmtIfElse(StmtIfElse *if_else) {
	m_parent = 0;
	m_if_else = if_else;
}

ConstraintStmtIfElse::~ConstraintStmtIfElse() {
	// TODO Auto-generated destructor stub
}

void ConstraintStmtIfElse::else_then(const std::function<void ()> &else_case) {
	uint32_t pre_size = RandObjCtor::inst().get_expressions().size();
	else_case();
	std::vector<IStmt *> stmts = RandObjCtor::inst().truncate_expressions(pre_size);

	// Link the 'else' case in. else_then is
	// a terminal, so no return
	m_if_else->false_case(new StmtBlock(stmts));
}

ConstraintStmtIfElse ConstraintStmtIfElse::else_if(
		const ConstraintBuilderExpr		&expr,
		const std::function<void ()> 	&else_case) {
	uint32_t pre_size = RandObjCtor::inst().get_expressions().size();
	else_case();
	std::vector<IStmt *> stmts = RandObjCtor::inst().truncate_expressions(pre_size);

	StmtIfElse *if_else = new StmtIfElse(
			expr.expr(),
			new StmtBlock(stmts));
	m_if_else->false_case(if_else);

	// Ensure a potential 'else' or 'if-else' can link itself in
	return ConstraintStmtIfElse(if_else);
}

} /* namespace ccrt */
