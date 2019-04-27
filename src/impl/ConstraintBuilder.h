/*
 * ConstraintBuilder.h
 *
 *  Created on: Apr 9, 2019
 *      Author: ballance
 */

#pragma once
#include <functional>
#include "IStmt.h"

namespace ccrt {

class ConstraintBuilder {
public:
	ConstraintBuilder(const std::string &name, const std::function<IStmt *()> &func);
	virtual ~ConstraintBuilder();
};

} /* namespace ccrt */

