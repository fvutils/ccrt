/*
 * RandObj.h
 *
 *  Created on: Mar 10, 2019
 *      Author: ballance
 */

#pragma once
#include "IRandObj.h"
#include <vector>
#include <string>
#include <functional>
#include "CtorScope.h"
#include "Constraint.h"
#include "Range.h"
#include <initializer_list>
#include <vector>
#include "boolector/boolector.h"
#include "impl/ConstraintStmtIfElse.h"

namespace ccrt {

class Expr;
class ConstraintStmt;
class VarBase;
class CovergroupModel;
template <typename T> class RandVar;
class RandObj : public virtual IRandObj {
public:
	template <typename T> friend class RandVar;
	template <typename T> friend class RandInst;
	friend class VarBase;
	friend class RandObjCtor;
	friend class Constraint;
	friend class CovergroupModel;
	RandObj();

	RandObj(const CtorScope &scope);

	virtual ~RandObj();

	virtual std::string toString();

protected:

	virtual void pre_randomize();

	virtual void post_randomize();

	void set_ref(IRandObj *ref);


	ConstraintStmtIfElse if_then(
			const ConstraintBuilderExpr 	&expr,
			const std::function<void ()>	&true_case
			);

	ConstraintBuilderExpr in(
			const ConstraintBuilderExpr		&expr,
			std::initializer_list<Range>	range);

	void constraint(ConstraintStmt &c);

private:
	bool do_randomize(BoolectorNode *with = 0);

	virtual void do_pre_randomize();

	virtual void do_post_randomize();

	virtual void get_constraints(std::vector<Constraint *> &constraints);

	virtual void get_variables(std::vector<VarBase *> &variables);

	void add_child(IRandObj *c);

	// Used to collect up all the variables in the system
	void add_variable(VarBase *var);

	void add_constraint(Constraint *c);


	void add_root_constraint(Constraint *c);

	virtual void finalize(RandObj *root);

	Btor *btor() { return m_btor; }

	// Returns the next seed value
	uint32_t next();

private:
	// handle to the parent object (or null if this is the root)
	RandObj								*m_parent;


	// Seed for the root object
	uint32_t							m_seed;

	uint32_t							m_depth;

	Btor								*m_btor;
	// TODO: handle to solver for this object

	std::vector<VarBase *>				m_variables;
	std::vector<Constraint *>			m_root_constraints;

	std::vector<IRandObj *>				m_children;

	std::vector<CovergroupModel *>		m_covergroups;

	// Collection of active constraint blocks for this type
	// Note: base classes are constructed before extended classes,
	// so we can iteratively 'kick out' overridden constraints
	std::vector<Constraint *>			m_constraints;

	bool								m_debug;

};

} /* namespace ccrt */

