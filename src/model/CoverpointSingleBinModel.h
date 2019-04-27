/*
 * CoverpointSingleBinModel.h
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */

#pragma once
#include <string>
#include <vector>

#include "ICoverpointBinModel.h"
#include "Range.h"


namespace ccrt {

class CoverpointSingleBinModel : public virtual ICoverpointBinModel {
public:
	CoverpointSingleBinModel(const std::string &name);

	virtual ~CoverpointSingleBinModel();

	void add_range(const Range &rng);

	virtual uint32_t num_bins() const { return 1; }

	virtual int32_t hit_idx() const;

	virtual void finalize();

	virtual void sample(const Value &v);

	virtual BoolectorNode *bin_constraint(uint32_t bin_idx);

private:
	std::vector<Range>			m_ranges;
	bool						m_hit;
};

} /* namespace ccrt */

