/*
 * IfElse.h
 *
 *  Created on: Mar 12, 2019
 *      Author: ballance
 */
#pragma once
#include "ccrt/impl/ConstraintStmt.h"

namespace ccrt {
class IfElse : public ConstraintStmt {
public:
	IfElse();

	virtual ~IfElse();

	IfElse &else_then(ConstraintStmt &c);

	IfElse &else_if(ConstraintStmt &c);
};

}
