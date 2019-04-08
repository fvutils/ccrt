/*
 * ExprUnaryOp.h
 *
 *  Created on: Apr 1, 2019
 *      Author: ballance
 */
#pragma once
#include "IExpr.h"
#include "ExprBase.h"

namespace ccrt {

class ExprUnaryOp : public ExprBase {
public:
	enum  OpType {
		UnOp_Not,
		UnOp_Neg
	};
public:
	ExprUnaryOp(OpType op, IExpr *rhs);

	virtual ~ExprUnaryOp();

	virtual Value value();

	virtual BoolectorNode *build_constraint(Btor *btor);

protected:
	OpType					m_op;
	IExpr					*m_rhs;
};

}

