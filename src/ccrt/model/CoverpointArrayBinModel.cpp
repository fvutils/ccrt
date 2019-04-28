/*
 * CoverpointArrayBinModel.cpp
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */

#include "ccrt/model/CoverpointArrayBinModel.h"

#include <string.h>

namespace ccrt {

CoverpointArrayBinModel::CoverpointArrayBinModel(
		const std::string		&name,
		uint64_t				low,
		uint64_t				high,
		int32_t					n_bins) {
	m_low = low;
	m_high = high;

	m_hit_idx = -1;

	int32_t actual_bins = n_bins;
	if (m_n_bins == -1) {
		actual_bins = (high-low+1);
		m_bin_stride = 1;
	} else {
		if (actual_bins > (high-low+1)) {
			actual_bins = (high-low+1);
		}
		m_bin_stride = ((high-low+1)/actual_bins);
	}
	m_n_bins = actual_bins;

	m_bins = new uint32_t[actual_bins];
	memset(m_bins, 0, sizeof(uint32_t)*actual_bins);
}

CoverpointArrayBinModel::~CoverpointArrayBinModel() {
	// TODO Auto-generated destructor stub
}

void CoverpointArrayBinModel::finalize() {

}

void CoverpointArrayBinModel::sample(const Value &v) {
	m_hit_idx = -1;
	uint64_t val = v.val_u();

	if (val >= m_low && val <= m_high) {
		// Compute the hit index
		m_hit_idx = (val-m_low)/m_bin_stride;

		// Increment the hit count
		m_bins[m_hit_idx]++;
	}
}

BoolectorNode *CoverpointArrayBinModel::bin_constraint(uint32_t bin_idx) {
	// TODO:
	return 0;
}

} /* namespace ccrt */
