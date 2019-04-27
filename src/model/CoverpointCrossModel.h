/*
 * CoverpointCrossModel.h
 *
 *  Created on: Apr 16, 2019
 *      Author: ballance
 */
#pragma once
#include <vector>
#include <stdint.h>
#include <unordered_set>

namespace ccrt {

class CoverpointModel;
class CoverageBinData;

class CoverpointCrossModel {
public:
	CoverpointCrossModel();

	virtual ~CoverpointCrossModel();

	void add_coverpoint(CoverpointModel *cp);

	void finalize();

	void sample();

	double get_coverage();

private:
	void sample(
			uint32_t					cp_idx,
			const std::vector<uint32_t>	&bin_idx_l);

private:
	std::vector<CoverpointModel *>		m_coverpoints;
	std::vector<uint32_t>				m_coverpoint_scale_factors;
	uint32_t							m_bin_data_len;
	CoverageBinData						*m_bin_data;
	std::unordered_set<uint32_t>		m_unhit_bins;
	std::unordered_set<uint32_t>		m_unreachable_bins;

};

} /* namespace ccrt */

