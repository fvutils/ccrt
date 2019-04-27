/*
 * ExprVarRef.cpp
 *
 *  Created on: Mar 23, 2019
 *      Author: ballance
 */

#include "model/ExprVarRef.h"

namespace ccrt {

ExprVarRef::ExprVarRef(const VarBase *var) :
		ExprBase(var->bits(), var->is_signed()), m_var(var) {
}

ExprVarRef::ExprVarRef(const VarBase &var) :
		ExprBase(var.bits(), var.is_signed()), m_var(&var) {
}

ExprVarRef::~ExprVarRef() {
	// TODO Auto-generated destructor stub
}

Value ExprVarRef::value() {
	fprintf(stdout, "-- ExprVarRef::value\n");
	return m_var->value();
}

BoolectorNode *ExprVarRef::build_constraint(Btor *btor) {
	return m_var->node();
}

} /* namespace ccrt */
