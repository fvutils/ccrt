/*
 * ConstraintBuilderExpr.h
 *
 *  Created on: Mar 16, 2019
 *      Author: ballance
 */
#pragma once
#include "boolector/boolector.h"

namespace ccrt {
class VarBase;

class ConstraintBuilderExpr {
public:
	// Conversion constructor
	ConstraintBuilderExpr(const VarBase &rhs);

	ConstraintBuilderExpr(uint32_t val);

	ConstraintBuilderExpr(
			BoolectorNode		*node,
			uint32_t			bits,
			bool				is_signed
			);

	virtual ~ConstraintBuilderExpr();

	BoolectorNode *node() const { return m_node; }

	uint32_t bits() const { return m_bits; }

	bool is_signed() const { return m_is_signed; }

	ConstraintBuilderExpr operator == (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator != (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator && (const ConstraintBuilderExpr &rhs);

private:
	BoolectorNode		*m_node;
	uint32_t			m_bits;
	bool				m_is_signed;

};

} /* namespace ccrt */

