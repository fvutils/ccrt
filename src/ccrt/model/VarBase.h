/*
 * VarBase.h
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */
#pragma once
#include "ccrt/IRandObj.h"
#include "ccrt/Range.h"
#include <stdint.h>
#include <string>

#include "ccrt/impl/ConstraintBuilderExpr.h"
#include "boolector/boolector.h"
#include "ccrt/model/Value.h"

namespace ccrt {

class RandObj;

class VarBase : public virtual IRandObj {
public:
	VarBase(
			const std::string 	&name,
			uint32_t			bits,
			bool				is_signed,
			bool				is_rand);

	virtual ~VarBase();

	virtual std::string toString();

	const std::string &name() const { return m_name; }

	BoolectorNode *node() const { return m_node; }

	uint32_t bits() const;

	bool is_signed() const;

	bool is_rand() const { return m_is_rand; }

	const Value &value() const;

	void value(const Value &v);

	virtual void finalize(RandObj *root);

	virtual void set_ref(IRandObj *ref);

//	ConstraintBuilderExpr operator ()();

	ConstraintBuilderExpr operator == (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator != (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator + (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator - (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator & (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator && (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator | (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator || (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator ! ();

	ConstraintBuilderExpr operator ~ ();

	ConstraintBuilderExpr operator < (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator <= (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator > (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator >= (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator [] (const Range &r);

	void in(const Range &r);

protected:
	Value				m_value;

private:
	virtual void do_pre_randomize();

	virtual void do_post_randomize();

	virtual void get_constraints(std::vector<Constraint *> &constraints);

	virtual void get_variables(std::vector<VarBase *> &variables);

private:
	RandObj				*m_parent;
	// Reference to the 'actual' variable. Defaults to
	// 'this', but can be set to another object when
	// we need to access a parallel structure -- for example
	// when working with a covergroup
	VarBase				*m_ref;
	BoolectorNode		*m_node;
	std::string			m_name;
	bool				m_is_rand;

};

}

