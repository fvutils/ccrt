/*
 * Bins.cpp
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */

#include "Bins.h"
#include <bits/stdc++.h>
#include <vector>
#include "ccrt/impl/RandObjCtor.h"
#include "ccrt/model/CoverpointArrayBinModel.h"
#include "ccrt/model/CoverpointCompoundBinModel.h"

namespace ccrt {

Bins::Bins(
		const std::string				&name,
		uint32_t						num_bins,
		std::initializer_list<Range>	bins) {
	// TODO Auto-generated constructor stub

}

Bins::Bins(
		const std::string				&name,
		std::initializer_list<Range>	bins) {
	CoverpointCompoundBinModel *compound_bins = 0;
	CoverpointArrayBinModel *array_bins = 0;
	std::vector<Range> bins_l = bins;

	// Sort the bins in order according to
	sort(bins_l.begin(), bins_l.end(), [](const Range &r1, const Range &r2) -> bool {
		return (r1.lhs() < r2.lhs());
	});

	// TODO: check for overlaps

	array_bins = new CoverpointArrayBinModel(name,
			bins_l.at(0).lhs(),
			bins_l.at(0).rhs());
	RandObjCtor::inst().add_coverpoint_bin(array_bins);

	// Create a single bin for each value in the bin list

//	if (compound_bins) {
//		return compound_bins;
//	} else {
//		return array_bins;
//	}
}

Bins::~Bins() {
	// TODO Auto-generated destructor stub
}

} /* namespace ccrt */
