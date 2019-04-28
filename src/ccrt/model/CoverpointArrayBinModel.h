/*
 * CoverpointArrayBinModel.h
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */
#pragma once
#include <stdint.h>
#include <string>
#include "ICoverpointBinModel.h"

namespace ccrt {

class CoverpointArrayBinModel : public virtual ICoverpointBinModel {
public:
	CoverpointArrayBinModel(
			const std::string		&name,
			uint64_t				low,
			uint64_t				high,
			int32_t					n_bins=-1);

	virtual ~CoverpointArrayBinModel();

	virtual uint32_t num_bins() const { return m_n_bins; }

	virtual int32_t hit_idx() const { return m_hit_idx; }

	virtual void finalize();

	virtual void sample(const Value &v);

	virtual BoolectorNode *bin_constraint(uint32_t bin_idx);

private:
	uint64_t				m_low;
	uint64_t				m_high;
	int32_t					m_n_bins;
	int32_t					m_hit_idx;

	// How big is each bin?
	uint32_t				m_bin_stride;
	uint32_t				*m_bins;

};

} /* namespace ccrt */

