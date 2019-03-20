/*
 * VarBase.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */

#include "VarBase.h"
#include <stdio.h>
#include "RandObjCtor.h"
#include "RandObj.h"

namespace ccrt {
VarBase::VarBase(
		const std::string		&name,
		uint32_t				bits,
		bool					is_signed,
		bool					is_rand) : m_name(name), m_bits(bits),
				m_is_signed(is_signed), m_is_rand(is_rand) {
	RandObjCtor &obj_ctor = RandObjCtor::inst();

	fprintf(stdout, "VarBase: %p\n", obj_ctor.scope());

	m_parent = obj_ctor.scope();

	Btor *btor = obj_ctor.scope()->btor();
	BoolectorSort sort = boolector_bitvec_sort(btor, bits);
	m_node = boolector_var(btor, sort, name.c_str());

	if (obj_ctor.scope()) {
		obj_ctor.scope()->add_child(this);
	} else {
		fprintf(stdout, "Error: Var created without a parent\n");
	}
	// TODO Auto-generated constructor stub

}

VarBase::~VarBase() {
	// TODO Auto-generated destructor stub
}

std::string VarBase::toString() {
	char tmp[64];

	if (m_is_signed) {
		sprintf(tmp, "%lld", m_value.ui64);
	} else {
		sprintf(tmp, "%llu", m_value.ui64);
	}

	std::string ret = m_name + " = " + tmp;

	return ret;
}

void VarBase::finalize(RandObj *root) {
	root->add_variable(this);
}

ConstraintBuilderExpr VarBase::operator ()() {
	return ConstraintBuilderExpr(m_node, m_bits, m_is_signed);
}

ConstraintBuilderExpr VarBase::operator == (const ConstraintBuilderExpr &rhs) {
	fprintf(stdout, "VarBase: EQ\n");
	return RandObjCtor::inst().push_eq((*this), rhs);
}

ConstraintBuilderExpr VarBase::operator != (const ConstraintBuilderExpr &rhs) {
	fprintf(stdout, "VarBase: NEQ\n");
	return RandObjCtor::inst().push_neq((*this), rhs);
}

ConstraintBuilderExpr VarBase::operator && (const ConstraintBuilderExpr &rhs) {
	fprintf(stdout, "VarBase: AND\n");
	return RandObjCtor::inst().push_logical_and((*this), rhs);
}

void VarBase::do_pre_randomize() {
	// TODO: if we're not random, add in appropriate constraints
}

void VarBase::do_post_randomize() {
	const char *val = boolector_bv_assignment(m_parent->btor(), m_node);

//	fprintf(stdout, "var %s=%s\n", m_name.c_str(), val);

	m_value.ui64 = 0;

	switch (m_bits) {
	case 1: {
		m_value.b = (val[0] == '1');

	} break;
	case 8: {
		for (uint32_t i=0; i<8; i++) {
			m_value.ui8 <<= 1;
			m_value.ui8 |= (val[i] == '1');
		}
	} break;

	case 16: {
		for (uint32_t i=0; i<16; i++) {
			m_value.ui16 <<= 1;
			m_value.ui16 |= (val[i] == '1');
		}
	} break;

	case 32: {
		for (uint32_t i=0; i<32; i++) {
			m_value.ui32 <<= 1;
			m_value.ui32 |= (val[i] == '1');
		}
	} break;

	case 64: {
		for (uint32_t i=0; i<64; i++) {
			m_value.ui64 <<= 1;
			m_value.ui64 |= (val[i] == '1');
		}
	} break;
	default:
		fprintf(stdout, "Error: unknown bits %d\n", m_bits);
	}
}

void VarBase::get_constraints(std::vector<Constraint *> &constraints) {
	// Do nothing
	// TODO: collect a constraint for non-rand variables
}

void VarBase::get_variables(std::vector<VarBase *> &variables) {
	variables.push_back(this);
}

}
