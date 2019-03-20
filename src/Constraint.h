/*
 * Constraint.h
 *
 *  Created on: Mar 16, 2019
 *      Author: ballance
 */

#pragma once
#include <functional>
#include <vector>
#include "boolector/boolector.h"

namespace ccrt {
class RandObj;

class Constraint {
public:
	Constraint(const std::string &name, const std::function<void ()> &func);
	virtual ~Constraint();

	const std::string &name() const { return m_name; }

	const std::vector<BoolectorNode *> &constraints() const {
		return m_constraints;
	}

	void finalize();

private:
	std::function<void ()> 					m_func;
	std::string								m_name;
	std::vector<BoolectorNode *>			m_constraints;

};

} /* namespace ccrt */

