/*
 * CoverpointBins.h
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */

#pragma once
#include <string>
#include <vector>
#include "Range.h"

namespace ccrt {

class CoverpointModel;

class CoverpointBins {
public:
	CoverpointBins(const std::string &name);

	virtual ~CoverpointBins();

private:
	std::vector<Range>					m_bins;
};

} /* namespace ccrt */

