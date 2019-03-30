/*
 * ExprVarRef.cpp
 *
 *  Created on: Mar 23, 2019
 *      Author: ballance
 */

#include "ExprVarRef.h"

namespace ccrt {

ExprVarRef::ExprVarRef(const VarBase *var) : ExprBase(var->bits(), var->is_signed()), m_var(var) {
	// TODO Auto-generated constructor stub

}

ExprVarRef::~ExprVarRef() {
	// TODO Auto-generated destructor stub
}

Value ExprVarRef::value() {
	return m_var->value();
}

BoolectorNode *ExprVarRef::build_constraint(Btor *btor) {
	return m_var->node();
}

} /* namespace ccrt */
