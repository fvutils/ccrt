/*
 * ExprBinaryOp.cpp
 *
 *  Created on: Mar 23, 2019
 *      Author: ballance
 */

#include "ExprBinaryOp.h"
#include <stdio.h>

namespace ccrt {

ExprBinaryOp::ExprBinaryOp(
		IExpr				*lhs,
		OpType				op,
		IExpr				*rhs) :
	ExprBase(0, false), m_lhs(lhs), m_op(op), m_rhs(rhs) {

	// Resize to the largest variable
	switch (op) {
	// Boolean operations
	case BinOp_Eq:
	case BinOp_Neq:
	case BinOp_Lt:
		m_bits = 1;
		break;

	default:
		m_bits = (lhs->bits() > rhs->bits())?lhs->bits():rhs->bits();
	}
}

ExprBinaryOp::~ExprBinaryOp() {
	// TODO Auto-generated destructor stub
}

Value ExprBinaryOp::value() {
	Value v;

	Value lhs = m_lhs->value();
	Value rhs = m_rhs->value();

	// Use the largest width
	// TODO: is this correct?
	v.bits = (lhs.bits>rhs.bits)?lhs.bits:rhs.bits;

	// TODO: determine whether the resulting value is signed or unsigned
	v.is_signed = false;

	if (v.is_signed) {
		switch (m_op) {
		case BinOp_Add:
			v.val_u(lhs.val_u() + rhs.val_u());
			break;
		case BinOp_Sub:
			v.val_u(lhs.val_u() - rhs.val_u());
			break;
		case BinOp_Mul:
			v.val_u(lhs.val_u() * rhs.val_u());
			break;
		case BinOp_Div:
			v.val_u(lhs.val_u() / rhs.val_u());
			break;
		case BinOp_Mod:
			v.val_u(lhs.val_u() % rhs.val_u());
			break;
		}
	} else {
		switch (m_op) {
		case BinOp_Add:
			v.val_s(lhs.val_s() + rhs.val_s());
			break;
		case BinOp_Sub:
			v.val_s(lhs.val_s() - rhs.val_s());
			break;
		case BinOp_Mul:
			v.val_s(lhs.val_s() * rhs.val_s());
			break;
		case BinOp_Div:
			v.val_s(lhs.val_s() / rhs.val_s());
			break;
		case BinOp_Mod:
			v.val_s(lhs.val_s() % rhs.val_s());
			break;
		}
	}

	return v;
}

BoolectorNode *ExprBinaryOp::build_constraint(Btor *btor) {
	BoolectorNode *lhs_n;
	BoolectorNode *rhs_n;
	BoolectorNode *ret = 0;
	bool is_signed;

	resize(btor, m_lhs, m_rhs, &lhs_n, &rhs_n, &is_signed);

	switch (m_op) {
	case BinOp_Add:
		ret = boolector_add(btor, lhs_n, rhs_n);
		break;
	case BinOp_Sub:
		ret = boolector_sub(btor, lhs_n, rhs_n);
		break;
	case BinOp_Mul:
		ret = boolector_mul(btor, lhs_n, rhs_n);
		break;
	case BinOp_Div:
		if (is_signed) {
			ret = boolector_sdiv(btor, lhs_n, rhs_n);
		} else {
			ret = boolector_udiv(btor, lhs_n, rhs_n);
		}
		break;
	case BinOp_Mod: {
		fprintf(stdout, "TODO: mod\n");
		break;

	case BinOp_Eq:
		ret = boolector_eq(btor, lhs_n, rhs_n);
		break;

	case BinOp_Neq:
		ret = boolector_not(btor, boolector_eq(btor, lhs_n, rhs_n));
		break;

	case BinOp_Lt:
		if (is_signed) {
			ret = boolector_slt(btor, lhs_n, rhs_n);
		} else {
			ret = boolector_ult(btor, lhs_n, rhs_n);
		}
		break;

	default:
		fprintf(stdout, "TODO: unhandled binary expression op %d\n", m_op);
	}

	}

	return ret;
}

} /* namespace ccrt */
