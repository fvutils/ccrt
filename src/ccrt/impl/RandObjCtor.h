/*
 * RandObjCtor.h
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */
#pragma once
#include <stack>
#include <vector>

#include "ccrt/impl/ConstraintBuilderExpr.h"
#include "ccrt/IStmt.h"
#include "ccrt/RandObj.h"

namespace ccrt {

class CtorScope;
class CoverpointBins;
class CovergroupModel;
class CoverpointModel;
class CoverpointCrossModel;
class ICoverpointBinModel;

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

	void set_covergroup_ctxt(CovergroupModel *cg);

	void add_coverpoint(CoverpointModel *cp);

	void add_crosspoint(CoverpointCrossModel *cross);

	void set_coverpoint_ctxt(CoverpointModel *cp);

	void add_coverpoint_bin(ICoverpointBinModel *bin);

	Btor *btor() const { return m_active_rand_obj->btor(); }

	ConstraintBuilderExpr push_eq(
			const ConstraintBuilderExpr &lhs,
			const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr push_neq(
			const ConstraintBuilderExpr &lhs,
			const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr push_plus(
			const ConstraintBuilderExpr &lhs,
			const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr push_minus(
			const ConstraintBuilderExpr &lhs,
			const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr push_logical_and(
			const ConstraintBuilderExpr &lhs,
			const ConstraintBuilderExpr &rhs);


	void push_expr(IStmt *expr);
	IStmt *pop_expr();

	const std::vector<IStmt *> &get_expressions() const {
		return m_expressions;
	}

	void clear_expr() {
		m_expressions.clear();
	}

	std::vector<IStmt *> truncate_expressions(uint32_t sz);

	void push_constraint(BoolectorNode *c);
	void pop_constraint(BoolectorNode *c);
	void pop_constraint(BoolectorNode *c1, BoolectorNode *c2);

	const std::vector<BoolectorNode *> &get_constraints() const {
		return m_constraints;
	}

	void clear_constraints() {
		m_constraints.clear();
	}


private:

	/**
	 * Resize two expressions to be the same size, and return the
	 * result in lhs_r and rhs_r
	 */
	void resize(
			const ConstraintBuilderExpr	&lhs,
			const ConstraintBuilderExpr &rhs,
			BoolectorNode **lhs_r, BoolectorNode **rhs_r);

	void enter(CtorScope *scope);

	void leave(CtorScope *scope);


private:
	std::vector<RandObj *>					m_scope_stack;
	std::vector<BoolectorNode *>			m_constraints;
	std::vector<IStmt *>					m_expressions;
//	std::stack<CtorScope>			m_scope_stack;
//	std::stack<RandObj *>			m_scope_stack;
	RandObj									*m_active_rand_obj;
	CovergroupModel							*m_covergroup;
	CoverpointModel							*m_coverpoint;
	static RandObjCtor						*m_inst;
};

}
