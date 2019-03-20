/*
 * VarBase.h
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */
#pragma once
#include "IRandObj.h"
#include <stdint.h>
#include <string>
#include "boolector/boolector.h"
#include "ConstraintBuilderExpr.h"

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

	uint32_t bits() const { return m_bits; }

	bool is_signed() const { return m_is_signed; }

	bool is_rand() const { return m_is_rand; }

	virtual void finalize(RandObj *root);

	ConstraintBuilderExpr operator ()();

	ConstraintBuilderExpr operator == (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator != (const ConstraintBuilderExpr &rhs);

	ConstraintBuilderExpr operator && (const ConstraintBuilderExpr &rhs);

protected:
	union val_t {
		uint64_t		ui64;
		int64_t			i64;
		uint32_t		ui32;
		int32_t			i32;
		uint16_t		ui16;
		int16_t			i16;
		uint8_t			ui8;
		int8_t			i8;
		bool			b;
	};

	val_t				m_value;

private:
	virtual void do_pre_randomize();

	virtual void do_post_randomize();

	virtual void get_constraints(std::vector<Constraint *> &constraints);

	virtual void get_variables(std::vector<VarBase *> &variables);

private:
	RandObj				*m_parent;
	BoolectorNode		*m_node;
	std::string			m_name;
	uint32_t			m_bits;
	bool				m_is_signed;
	bool				m_is_rand;

};

}

