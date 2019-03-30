/*
 * ConstraintBuilderExpr.h
 *
 *  Created on: Mar 16, 2019
 *      Author: ballance
 */
#pragma once
#include <memory>
#include "boolector/boolector.h"
#include "IExpr.h"

namespace ccrt {
class VarBase;

class ConstraintBuilderExpr {
public:
	// Conversion constructor
	ConstraintBuilderExpr(const VarBase &rhs);

	ConstraintBuilderExpr(uint32_t val);

	ConstraintBuilderExpr(IExpr *expr);

	virtual ~ConstraintBuilderExpr();

	IExpr *expr() const { return m_expr; }

	uint32_t bits() const { return m_expr->bits(); }

	bool is_signed() const { return m_expr->is_signed(); }

	ConstraintBuilderExpr operator == (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator != (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator + (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator - (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator && (const ConstraintBuilderExpr &rhs);

private:
	IExpr						*m_expr;

};

} /* namespace ccrt */

