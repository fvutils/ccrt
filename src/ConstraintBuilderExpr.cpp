/*
 * ConstraintBuilderExpr.cpp
 *
 *  Created on: Mar 16, 2019
 *      Author: ballance
 */

#include "ConstraintBuilderExpr.h"
#include "RandObjCtor.h"
#include "VarBase.h"
#include <stdio.h>

namespace ccrt {

ConstraintBuilderExpr::ConstraintBuilderExpr(
		BoolectorNode			*node,
		uint32_t				bits,
		bool					is_signed) :
				m_node(node),
				m_bits(bits),
				m_is_signed(is_signed) {
	fprintf(stdout, "ConstraintBuilderExpr: %p\n", this);
	RandObjCtor::inst().push_constraint(node);
}

ConstraintBuilderExpr::ConstraintBuilderExpr(const VarBase &var) {
	m_node = var.node();
	m_bits = var.bits();
	m_is_signed = var.is_signed();
	fprintf(stdout, "ConstraintBuilderExpr(var): %p\n", this);
	RandObjCtor::inst().push_constraint(m_node);
}

ConstraintBuilderExpr::~ConstraintBuilderExpr() {
	fprintf(stdout, "~ConstraintBuilderExpr: %p\n", this);
	// TODO Auto-generated destructor stub
}

ConstraintBuilderExpr ConstraintBuilderExpr::operator ==(const ConstraintBuilderExpr &rhs) {
	// TODO: create an == node from this node and the rhs
	fprintf(stdout, "-- EQ\n");

	return ConstraintBuilderExpr(0,0,0);
}

ConstraintBuilderExpr ConstraintBuilderExpr::operator &&(const ConstraintBuilderExpr &rhs) {
	return RandObjCtor::inst().push_logical_and(*this, rhs);
}

} /* namespace ccrt */
