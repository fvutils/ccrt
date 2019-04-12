/*
 * ExprIn.h
 *
 *  Created on: Apr 12, 2019
 *      Author: ballance
 */

#pragma once
#include <vector>
#include "ExprBase.h"
#include "IExpr.h"
#include "Range.h"

namespace ccrt {

class ExprIn : public ExprBase {
public:
	ExprIn(
			IExpr						*lhs,
			const std::vector<Range>	&rhs
			);

	virtual ~ExprIn();

	virtual BoolectorNode *build_constraint(Btor *btor);

	virtual Value value();


private:
	IExpr					*m_lhs;
	std::vector<Range>		m_rhs;

};

} /* namespace ccrt */

