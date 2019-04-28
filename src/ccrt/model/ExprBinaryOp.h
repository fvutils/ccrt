/*
 * ExprBinaryOp.h
 *
 *  Created on: Mar 23, 2019
 *      Author: ballance
 */

#pragma once
#include <memory>
#include "ccrt/model/ExprBase.h"

namespace ccrt {

class ExprBinaryOp : public ExprBase {
public:
	enum OpType {
		BinOp_Add,
		BinOp_And,
		BinOp_Or,
		BinOp_Sub,
		BinOp_Mul,
		BinOp_Div,
		BinOp_Mod,
		BinOp_Eq,
		BinOp_Gt,
		BinOp_Ge,
		BinOp_Neq,
		BinOp_AndAnd,
		BinOp_OrOr,
		BinOp_Le,
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

