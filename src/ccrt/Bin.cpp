/*
 * Bin.cpp
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */

#include <stdio.h>
#include "Bin.h"
#include "ccrt/model/CoverpointSingleBinModel.h"
#include "ccrt/impl/RandObjCtor.h"

namespace ccrt {

Bin::Bin(
		const std::string				&name,
		std::initializer_list<Range>	bins) {

	m_model = new CoverpointSingleBinModel(name);

	for (std::initializer_list<Range>::iterator it=bins.begin();
			it!=bins.end(); it++) {
		m_model->add_range(*it);
	}

	RandObjCtor::inst().add_coverpoint_bin(m_model);
	fprintf(stdout, "bin: n_bins=%d name=%s\n",
			bins.size(), name.c_str());
}

Bin::~Bin() {
	// TODO Auto-generated destructor stub
}

} /* namespace ccrt */
