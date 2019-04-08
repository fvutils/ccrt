/*
 * ExprPartSelect.cpp
 *
 *  Created on: Apr 1, 2019
 *      Author: ballance
 */

#include "ExprPartSelect.h"

namespace ccrt {

ExprPartSelect::ExprPartSelect(IExpr *base, const Range &r) :
		ExprBase((r.lhs()>r.rhs())?(r.lhs()-r.rhs()+1):(r.rhs()-r.lhs()+1), base->is_signed()),
		m_base(base), m_range(r) {

}

ExprPartSelect::~ExprPartSelect() {
	// TODO Auto-generated destructor stub
}

Value ExprPartSelect::value() {
	fprintf(stdout, "TODO: ExprPartSelect::value()\n");
}

BoolectorNode *ExprPartSelect::build_constraint(Btor *btor) {
	uint32_t upper = (m_range.lhs()>m_range.rhs())?m_range.lhs():m_range.rhs();
	uint32_t lower = (m_range.lhs()<m_range.rhs())?m_range.lhs():m_range.rhs();

	fprintf(stdout, "Select: [%d:%d]\n", upper, lower);

	return boolector_slice(btor,
			m_base->build_constraint(btor),
			upper,
			lower);
}

} /* namespace ccrt */
