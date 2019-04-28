/*
 * CoverpointSingleBinModel.cpp
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */

#include "ccrt/model/CoverpointSingleBinModel.h"

namespace ccrt {

CoverpointSingleBinModel::CoverpointSingleBinModel(const std::string &name) {
	// TODO Auto-generated constructor stub

}

CoverpointSingleBinModel::~CoverpointSingleBinModel() {
	// TODO Auto-generated destructor stub
}

void CoverpointSingleBinModel::add_range(const Range &rng) {
	m_ranges.push_back(rng);

}

int32_t CoverpointSingleBinModel::hit_idx() const {
	if (m_hit) {
		return 0;
	} else {
		return -1;
	}
}

void CoverpointSingleBinModel::finalize() {
	// TODO: sort bin by value. We need to eliminate any overlaps
}

void CoverpointSingleBinModel::sample(const Value &v) {
	m_hit = false;

	for (std::vector<Range>::const_iterator it=m_ranges.begin();
			it!=m_ranges.end(); it++) {
		// TODO: should probably do a better comparison
		if (v.val.u64 >= it->lhs() && v.val.u64 <= it->rhs()) {
			m_hit = true;
		}

		fprintf(stdout, "sample: v=%lld ; hit=%d\n", v.val.u64, m_hit);
	}
}

BoolectorNode *CoverpointSingleBinModel::bin_constraint(uint32_t bin_idx) {
	// TODO:
	return 0;
}

} /* namespace ccrt */
