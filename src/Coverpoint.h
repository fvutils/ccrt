/*
 * Coverpoint.h
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */
#pragma once
#include <string>
#include <functional>
#include "impl/ConstraintBuilderExpr.h"


namespace ccrt {
class CoverpointModel;
class Cross;

class Coverpoint {
public:
	friend class Cross;

	Coverpoint(
			const std::string 				&name,
			const ConstraintBuilderExpr		&expr,
			const std::function<void ()>	&bins);

	virtual ~Coverpoint();

	int			m_goal;

protected:
	CoverpointModel *model() const { return m_model; }

private:
	CoverpointModel							*m_model;

};

} /* namespace ccrt */

