/*
 * Coverpoint.cpp
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */

#include "Coverpoint.h"
#include "ccrt/model/CoverpointModel.h"
#include "ccrt/impl/RandObjCtor.h"

namespace ccrt {

Coverpoint::Coverpoint(
			const std::string 				&name,
			const ConstraintBuilderExpr		&expr,
			const std::function<void ()>	&bins) {
	m_model = new CoverpointModel(name, expr.expr());

	RandObjCtor::inst().add_coverpoint(m_model);
	RandObjCtor::inst().set_coverpoint_ctxt(m_model);

	// build bins
	bins();

	RandObjCtor::inst().set_coverpoint_ctxt(0);
}

Coverpoint::~Coverpoint() {
	// TODO Auto-generated destructor stub
}

} /* namespace ccrt */
