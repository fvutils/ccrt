/*
 * ConstraintStmt.h
 *
 *  Created on: Mar 12, 2019
 *      Author: ballance
 */
#pragma once

#include <functional>

#include "ccrt/impl/ConstraintBuilderExpr.h"

namespace ccrt {

class ConstraintStmt {
public:
	ConstraintStmt();

	virtual ~ConstraintStmt();


};

void implies(const ConstraintBuilderExpr &e, const std::function<void ()> &func);

}
