/*
 * Constraint.h
 *
 *  Created on: Mar 16, 2019
 *      Author: ballance
 */

#pragma once
#include <functional>

namespace ccrt {

class Constraint {
public:
	Constraint(const std::string &name, const std::function<void ()> &func);
	virtual ~Constraint();

private:

};

} /* namespace ccrt */

