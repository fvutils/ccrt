/*
 * ExprBinaryOp.h
 *
 *  Created on: Mar 23, 2019
 *      Author: ballance
 */

#pragma once
#include "ExprBase.h"
#include <memory>

namespace ccrt {

class ExprBinaryOp : public ExprBase {
public:
	enum OpType {
		BinOp_Add,
		BinOp_Sub,
		BinOp_Mul,
		BinOp_Div,
		BinOp_Mod,
		BinOp_Eq,
		BinOp_Neq,
		BinOp_AndAnd,
		BinOp_Lt
	};
public:
	ExprBinaryOp(
			IExpr			*lhs,
			OpType			op,
			IExpr			*rhs
			);

	virtual ~ExprBinaryOp();

	virtual Value value();

	virtual BoolectorNode *build_constraint(Btor *btor);

protected:
	IExpr					*m_lhs;
	OpType					m_op;
	IExpr					*m_rhs;

};

} /* namespace ccrt */

