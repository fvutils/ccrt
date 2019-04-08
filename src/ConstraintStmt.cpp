/*
 * ConstraintStmt.cpp
 *
 *  Created on: Mar 12, 2019
 *      Author: ballance
 */

#include "ConstraintStmt.h"
#include "StmtImplies.h"
#include "ExprLiteral.h"
#include "RandObjCtor.h"

namespace ccrt {
ConstraintStmt::ConstraintStmt() {
	// TODO Auto-generated constructor stub

}

ConstraintStmt::~ConstraintStmt() {
	// TODO Auto-generated destructor stub
}

void implies(const ConstraintBuilderExpr &e, const std::function<void ()> &func) {
	// Pop the expression off the stack
	RandObjCtor::inst().pop_expr();

	uint32_t pre_size = RandObjCtor::inst().get_expressions().size();
	func();
	std::vector<IStmt *> stmts = RandObjCtor::inst().truncate_expressions(pre_size);

	if (stmts.size() == 0) {
		stmts.push_back(new ExprLiteral(1, 1, false));
	}

	RandObjCtor::inst().push_expr(
			new StmtImplies(e.expr(), stmts));
}


}
