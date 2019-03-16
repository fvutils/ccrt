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
		bool					is_signed) : m_name(name), m_bits(bits), m_is_signed(is_signed) {
	RandObjCtor &obj_ctor = RandObjCtor::inst();

	fprintf(stdout, "VarBase: %p\n", obj_ctor.scope());

	m_parent = obj_ctor.scope();

	Btor *btor = obj_ctor.scope()->btor();
	BoolectorSort sort = boolector_bitvec_sort(btor, bits);
	m_node = boolector_var(btor, sort, name.c_str());

	if (obj_ctor.scope()) {
		obj_ctor.scope()->add_field(this);
	} else {
		fprintf(stdout, "Error: Var created without a parent\n");
	}
	// TODO Auto-generated constructor stub

}

VarBase::~VarBase() {
	// TODO Auto-generated destructor stub
}

std::string VarBase::toString() {
	std::string ret = m_name + " = ";
	ret += boolector_bv_assignment(m_parent->btor(), m_node);

	return ret;
}

}
