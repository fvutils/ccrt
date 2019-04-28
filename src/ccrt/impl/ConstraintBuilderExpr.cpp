/*
 * ConstraintBuilderExpr.cpp
 *
 *  Created on: Mar 16, 2019
 *      Author: ballance
 */

#include "ccrt/impl/ConstraintBuilderExpr.h"

#include <stdio.h>
#include "ccrt/model/ExprBinaryOp.h"
#include "ccrt/model/ExprLiteral.h"
#include "ccrt/model/ExprVarRef.h"
#include "ccrt/model/VarBase.h"
#include "ccrt/impl/RandObjCtor.h"

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
	RandObjCtor::inst().pop_expr();
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					expr(),
					ExprBinaryOp::BinOp_Eq,
					rhs.expr()));
}

ConstraintBuilderExpr ConstraintBuilderExpr::operator !=(const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					expr(),
					ExprBinaryOp::BinOp_Neq,
					rhs.expr()));
}

ConstraintBuilderExpr ConstraintBuilderExpr::operator + (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					expr(),
					ExprBinaryOp::BinOp_Add,
					rhs.expr()));
}

ConstraintBuilderExpr ConstraintBuilderExpr::operator - (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					expr(),
					ExprBinaryOp::BinOp_Sub,
					rhs.expr()));
}

ConstraintBuilderExpr ConstraintBuilderExpr::operator &&(const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					expr(),
					ExprBinaryOp::BinOp_AndAnd,
					rhs.expr()));
}


ConstraintBuilderExpr ConstraintBuilderExpr::operator < (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					expr(),
					ExprBinaryOp::BinOp_Lt,
					rhs.expr()));
}

ConstraintBuilderExpr ConstraintBuilderExpr::operator <= (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					expr(),
					ExprBinaryOp::BinOp_Le,
					rhs.expr()));
}

ConstraintBuilderExpr ConstraintBuilderExpr::operator > (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					expr(),
					ExprBinaryOp::BinOp_Gt,
					rhs.expr()));
}

ConstraintBuilderExpr ConstraintBuilderExpr::operator >= (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					expr(),
					ExprBinaryOp::BinOp_Ge,
					rhs.expr()));
}

} /* namespace ccrt */
