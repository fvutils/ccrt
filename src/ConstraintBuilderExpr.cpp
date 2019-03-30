/*
 * ConstraintBuilderExpr.cpp
 *
 *  Created on: Mar 16, 2019
 *      Author: ballance
 */

#include "ConstraintBuilderExpr.h"
#include "RandObjCtor.h"
#include "VarBase.h"
#include "ExprVarRef.h"
#include "ExprLiteral.h"
#include <stdio.h>

namespace ccrt {

ConstraintBuilderExpr::ConstraintBuilderExpr(IExpr *expr) : m_expr(expr) {
	fprintf(stdout, "ConstraintBuilderExpr: %p\n", this);
	RandObjCtor::inst().push_expr(m_expr);
//	RandObjCtor::inst().push_constraint(node);
}

ConstraintBuilderExpr::ConstraintBuilderExpr(const VarBase &var) :
		m_expr(new ExprVarRef(&var)) {
	fprintf(stdout, "ConstraintBuilderExpr(var): %p\n", this);
	RandObjCtor::inst().push_expr(m_expr);
//	RandObjCtor::inst().push_constraint(m_node);
}

ConstraintBuilderExpr::ConstraintBuilderExpr(uint32_t val) :
		m_expr(new ExprLiteral(val, 32, false)) {
	RandObjCtor::inst().push_expr(m_expr);

//	RandObjCtor &ctor = RandObjCtor::inst();
//	char tmp[64];
//
//	sprintf(tmp, "%d", val);
//
//	m_node = boolector_constd(ctor.btor(),
//			boolector_bitvec_sort(ctor.btor(), 32),
//			tmp);
//	m_bits = 32;
//	m_is_signed = false;
//	RandObjCtor::inst().push_constraint(m_node);
}

ConstraintBuilderExpr::~ConstraintBuilderExpr() {
	fprintf(stdout, "~ConstraintBuilderExpr: %p\n", this);
	// TODO Auto-generated destructor stub
}

ConstraintBuilderExpr ConstraintBuilderExpr::operator ==(const ConstraintBuilderExpr &rhs) {
//
//	// TODO: create an == node from this node and the rhs
//	fprintf(stdout, "-- TODO: EQ\n");
//
//	return ConstraintBuilderExpr(0,0,0);
}

ConstraintBuilderExpr ConstraintBuilderExpr::operator !=(const ConstraintBuilderExpr &rhs) {
	// TODO: create an == node from this node and the rhs
//	fprintf(stdout, "-- NEQ\n");
//
//	return ConstraintBuilderExpr(0,0,0);
}

ConstraintBuilderExpr ConstraintBuilderExpr::operator &&(const ConstraintBuilderExpr &rhs) {
	fprintf(stdout, "-- AND\n");
	return RandObjCtor::inst().push_logical_and(*this, rhs);
}

} /* namespace ccrt */
