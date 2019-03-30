/*
 * ExprLiteral.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: ballance
 */

#include "ExprLiteral.h"

namespace ccrt {

ExprLiteral::ExprLiteral(uint64_t val, uint32_t bits, bool is_signed) :
		ExprBase(bits, is_signed) {

	m_val.bits = bits;
	m_val.is_signed = is_signed;

	if (is_signed) {
		m_val.val_s((int32_t)val);
	} else {
		m_val.val_u(val);
	}
	// TODO: capture value
}

ExprLiteral::~ExprLiteral() {
	// TODO Auto-generated destructor stub
}

Value ExprLiteral::value() {
	return m_val;
}

BoolectorNode *ExprLiteral::build_constraint(Btor *btor) {
	char tmp[128];

	uint64_t val = m_val.val_u();
	for (uint32_t i=0; i<m_val.bits; i++) {
		tmp[m_val.bits-i-1] = (val & (1 << i))?'1':'0';
	}
	tmp[m_val.bits] = 0;

//	fprintf(stdout, "literal: bits=%d \"%s\"\n", m_val.bits, tmp);
//
//	sprintf(tmp, "%lld", val);
//
//	return boolector_constd(btor,
//			boolector_bitvec_sort(btor, m_val.bits),
//			tmp);
	return boolector_const(btor, tmp);
}

} /* namespace ccrt */
