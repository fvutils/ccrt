/*
 * ExprBase.cpp
 *
 *  Created on: Mar 23, 2019
 *      Author: ballance
 */

#include "ExprBase.h"

namespace ccrt {

ExprBase::ExprBase(uint32_t bits, bool is_signed) : m_bits(bits), m_is_signed(is_signed) {
	// TODO Auto-generated constructor stub

}

ExprBase::~ExprBase() {
	// TODO Auto-generated destructor stub
}

void ExprBase::resize(
		Btor							*btor,
		IExpr							*v1,
		IExpr							*v2,
		BoolectorNode					**v1_n,
		BoolectorNode					**v2_n,
		bool							*is_signed) {
	*v1_n = v1->build_constraint(btor);
	*v2_n = v2->build_constraint(btor);

	// TODO: need to figure out sign resolution
	*is_signed = (v1->is_signed() && v2->is_signed());

	fprintf(stdout, "resize: v1.bits=%d v2.bits=%d\n",
			v1->bits(), v2->bits());

	if (v1->bits() > v2->bits()) {
		if (v2->is_signed()) {
			*v2_n = boolector_sext(
					btor,
					*v2_n,
					(v1->bits()-v2->bits()));
		} else {
			*v2_n = boolector_uext(
					btor,
					*v2_n,
					(v1->bits()-v2->bits()));
		}
	} else if (v2->bits() > v1->bits()) {
		if (v1->is_signed()) {
			*v1_n = boolector_sext(
					btor,
					*v1_n,
					(v2->bits()-v1->bits()));
		} else {
			*v1_n = boolector_uext(
					btor,
					*v1_n,
					(v2->bits()-v1->bits()));
		}
	}
}

} /* namespace ccrt */
