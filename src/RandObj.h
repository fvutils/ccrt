/*
 * RandObj.h
 *
 *  Created on: Mar 10, 2019
 *      Author: ballance
 */

#pragma once
#include <vector>
#include <string>
#include "CtorScope.h"
#include "IfElse.h"
#include "boolector/boolector.h"

namespace ccrt {

class Expr;
class ConstraintStmt;
class VarBase;
template <typename T> class RandVar;
class RandObj {
public:
	template <typename T> friend class RandVar;
	friend class VarBase;
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

	void add_field(VarBase *f);

	void add_child(RandObj *c);

	Btor *btor() { return m_btor; }

private:
	// handle to the parent object (or null if this is the root)
	RandObj						*m_parent;

	Btor						*m_btor;
	// TODO: handle to solver for this object

	std::vector<VarBase *>		m_fields;
	std::vector<RandObj *>		m_children;

};

} /* namespace ccrt */

