/*
 * ExprIn.cpp
 *
 *  Created on: Apr 12, 2019
 *      Author: ballance
 */

#include "ccrt/model/ExprIn.h"

namespace ccrt {

ExprIn::ExprIn(
		IExpr						*lhs,
		const std::vector<Range>	&rhs) : ExprBase(1, false),
				m_lhs(lhs), m_rhs(rhs) {

}

ExprIn::~ExprIn() {
	// TODO Auto-generated destructor stub
}

BoolectorNode *ExprIn::build_constraint(Btor *btor) {
	BoolectorNode *ret = 0;

	for (std::vector<Range>::const_iterator it=m_rhs.begin();
			it!=m_rhs.end(); it++) {
		// TODO: figure out signed-ness

		// Create the term
		BoolectorNode *term = 0;
		BoolectorNode *lhs = m_lhs->build_constraint(btor);

		if (m_lhs->bits() < 32) {
			if (m_lhs->is_signed()) {
				lhs = boolector_uext(btor, lhs, (32-m_lhs->bits()));
			} else {
				lhs = boolector_sext(btor, lhs, (32-m_lhs->bits()));
			}
		}

		if (it->rhs() == it->lhs()) {
			char bits[64];

			for (uint32_t i=0; i<32; i++) {
				bits[32-i-1] = (it->rhs() & (1 << i))?'1':'0';
			}
			bits[32] = 0;

			// single value
			term = boolector_eq(btor, lhs,
					boolector_const(btor, bits));
		} else {
			// range
			char bits_l[64], bits_r[64];

			for (uint32_t i=0; i<32; i++) {
				bits_l[32-i-1] = (it->lhs() & (1 << i))?'1':'0';
				bits_r[32-i-1] = (it->rhs() & (1 << i))?'1':'0';
			}
			bits_l[32] = 0;
			bits_r[32] = 0;

			fprintf(stdout, "bits_l=%s bits_r=%s\n", bits_l, bits_r);

			// Range
			term = boolector_and(btor,
					boolector_sgte(btor, lhs,
							boolector_const(btor, bits_l)),
					boolector_slte(btor, lhs,
							boolector_const(btor, bits_r))
					);
		}

		if (ret) {
			ret = boolector_or(btor, ret, term);
		} else {
			ret = term;
		}
	}

	return ret;
}

Value ExprIn::value() {
	// TODO:
}

} /* namespace ccrt */
