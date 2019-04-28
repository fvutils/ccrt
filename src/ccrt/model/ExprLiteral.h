/*
 * ExprLiteral.h
 *
 *  Created on: Mar 24, 2019
 *      Author: ballance
 */
#pragma once
#include "ccrt/model/ExprBase.h"

namespace ccrt {

class ExprLiteral : public ExprBase {
public:
	ExprLiteral(uint64_t val, uint32_t bits, bool is_signed);

	virtual ~ExprLiteral();

	virtual Value value();

	virtual BoolectorNode *build_constraint(Btor *btor);

private:
	Value			m_val;
};

} /* namespace ccrt */

