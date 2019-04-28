/*
 * ExprVarRef.h
 *
 *  Created on: Mar 23, 2019
 *      Author: ballance
 */

#pragma once
#include "ccrt/model/ExprBase.h"
#include "VarBase.h"

namespace ccrt {

class ExprVarRef : public ExprBase {
public:

	ExprVarRef(const VarBase *var);

	ExprVarRef(const VarBase &var);

	virtual ~ExprVarRef();

	virtual Value value();

	virtual BoolectorNode *build_constraint(Btor *btor);

private:
	const VarBase				*m_var;

};

} /* namespace ccrt */

