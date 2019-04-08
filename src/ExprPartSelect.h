/*
 * ExprPartSelect.h
 *
 *  Created on: Apr 1, 2019
 *      Author: ballance
 */
#pragma once
#include "ExprBase.h"
#include "IExpr.h"
#include "Range.h"

namespace ccrt {

class ExprPartSelect : public ExprBase {
public:
	ExprPartSelect(IExpr *base, const Range &r);

	virtual ~ExprPartSelect();

	virtual Value value();

	virtual BoolectorNode *build_constraint(Btor *btor);

private:
	IExpr				*m_base;
	Range				m_range;

};

} /* namespace ccrt */

