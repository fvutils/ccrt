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
	RandObjCtor::inst().push_expr(m_expr);
}

ConstraintBuilderExpr::ConstraintBuilderExpr(const VarBase &var) :
		m_expr(new ExprVarRef(&var)) {
	RandObjCtor::inst().push_expr(m_expr);
}

ConstraintBuilderExpr::ConstraintBuilderExpr(uint32_t val) :
		m_expr(new ExprLiteral(val, 32, false)) {
	RandObjCtor::inst().push_expr(m_expr);
}

ConstraintBuilderExpr::~ConstraintBuilderExpr() {
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
