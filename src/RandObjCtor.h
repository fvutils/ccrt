/*
 * RandObjCtor.h
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */
#pragma once
#include <stack>
#include <vector>
#include "RandObj.h"
#include "ConstraintBuilderExpr.h"

namespace ccrt {

class CtorScope;

class RandObjCtor {
public:
	friend class CtorScope;
	RandObjCtor();

	virtual ~RandObjCtor();

	static RandObjCtor &inst();

	static std::string auto_name();

	RandObj *scope() const;

	RandObj *parent() const;

	void set_active_rand_obj(RandObj *obj) { m_active_rand_obj = obj; }

	Btor *btor() const { return m_active_rand_obj->btor(); }

	ConstraintBuilderExpr push_eq(
			const ConstraintBuilderExpr &lhs,
			const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr push_logical_and(
			const ConstraintBuilderExpr &lhs,
			const ConstraintBuilderExpr &rhs);

	void push_constraint(BoolectorNode *c);
	void pop_constraint(BoolectorNode *c);
	void pop_constraint(BoolectorNode *c1, BoolectorNode *c2);


private:

	void enter(CtorScope *scope);

	void leave(CtorScope *scope);


private:
	std::vector<RandObj *>					m_scope_stack;
	std::vector<BoolectorNode *>			m_constraints;
//	std::stack<CtorScope>			m_scope_stack;
//	std::stack<RandObj *>			m_scope_stack;
	RandObj									*m_active_rand_obj;
	static RandObjCtor						*m_inst;
};

}
