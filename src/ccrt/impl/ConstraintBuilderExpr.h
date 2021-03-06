/*
 * ConstraintBuilderExpr.h
 *
 *  Created on: Mar 16, 2019
 *      Author: ballance
 */
#pragma once
#include <memory>
#include <functional>
#include "boolector/boolector.h"
#include "ccrt/model/IExpr.h"
#include "ccrt/Range.h"

namespace ccrt {
class VarBase;

class ConstraintBuilderExpr {
public:
	// Conversion constructor
	ConstraintBuilderExpr(const VarBase &rhs);

	ConstraintBuilderExpr(uint32_t val);

	ConstraintBuilderExpr(IExpr *expr);

	ConstraintBuilderExpr(const Range &r);

	virtual ~ConstraintBuilderExpr();

	IExpr *expr() const { return m_expr; }

	uint32_t bits() const { return m_expr->bits(); }

	bool is_signed() const { return m_expr->is_signed(); }

	ConstraintBuilderExpr operator == (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator != (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator + (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator - (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator && (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator < (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator <= (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator > (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator >= (const ConstraintBuilderExpr &rhs);

private:
	IExpr						*m_expr;

};


} /* namespace ccrt */

