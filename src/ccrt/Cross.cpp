/*
 * Cross.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: ballance
 */

#include "Cross.h"
#include "Coverpoint.h"
#include "ccrt/impl/RandObjCtor.h"
#include "ccrt/model/CoverpointCrossModel.h"

namespace ccrt {

Cross::Cross(
		const std::string 						&name,
		std::initializer_list<Coverpoint>		cp_list) {

	fprintf(stdout, "Note: %d cross items\n", cp_list.size());
	// TODO Auto-generated constructor stub

	m_model = new CoverpointCrossModel();

	for (std::initializer_list<Coverpoint>::iterator it=cp_list.begin();
			it!=cp_list.end(); it++) {
		m_model->add_coverpoint(it->model());
	}

	RandObjCtor::inst().add_crosspoint(m_model);
}

Cross::~Cross() {
	// TODO Auto-generated destructor stub
}

} /* namespace ccrt */
