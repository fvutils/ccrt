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
#include "CtorScope.h"
#include "IfElse.h"
#include "Constraint.h"
#include "boolector/boolector.h"

namespace ccrt {

class Expr;
class ConstraintStmt;
class VarBase;
template <typename T> class RandVar;
class RandObj : public virtual IRandObj {
public:
	template <typename T> friend class RandVar;
	friend class VarBase;
	friend class RandObjCtor;
	RandObj();

	RandObj(const CtorScope &scope);

	virtual ~RandObj();

	virtual std::string toString();

protected:

	virtual void pre_randomize();

	virtual void post_randomize();



	IfElse &if_then();

	void constraint(ConstraintStmt &c);

private:
	bool do_randomize();

	virtual void do_pre_randomize();

	virtual void do_post_randomize();

	void add_child(IRandObj *c);

	// Used to collect up all the variables in the system
	void add_variable(VarBase *var);

	void add_constraint(Constraint *c);

	virtual void finalize(RandObj *root);

	Btor *btor() { return m_btor; }

private:
	// handle to the parent object (or null if this is the root)
	RandObj						*m_parent;

	Btor						*m_btor;
	// TODO: handle to solver for this object

	std::vector<VarBase *>		m_variables;
	std::vector<IRandObj *>		m_children;

	// Collection of active constraint blocks for this type
	// Note: base classes are constructed before extended classes,
	// so we can iteratively 'kick out' overridden constraints
	std::vector<Constraint *>	m_constraints;

};

} /* namespace ccrt */

