/*
 * ExprUnaryOp.cpp
 *
 *  Created on: Apr 1, 2019
 *      Author: ballance
 */

#include "model/ExprUnaryOp.h"

namespace ccrt {

ExprUnaryOp::ExprUnaryOp(ExprUnaryOp::OpType op, IExpr *rhs) :
		ExprBase(rhs->bits(), rhs->is_signed()),
		m_op(op), m_rhs(rhs) {
	// TODO Auto-generated constructor stub

	if (op == UnOp_Not) {
		bits(1);
		is_signed(false);
	}
}

ExprUnaryOp::~ExprUnaryOp() {
	// TODO Auto-generated destructor stub
}

Value ExprUnaryOp::value() {
	Value v;

	// TODO:

	return v;
}

BoolectorNode *ExprUnaryOp::build_constraint(Btor *btor) {
	BoolectorNode *ret = 0;

	BoolectorNode *v_n;

	switch (m_op) {
	case UnOp_Not:
		to_boolean(btor, m_rhs, &v_n);
		ret = boolector_not(btor, v_n);
		break;

	case UnOp_Neg:
		v_n = m_rhs->build_constraint(btor);
		ret = boolector_not(btor, v_n);
		break;
	}

	return ret;
}

}
