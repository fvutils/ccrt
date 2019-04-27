/*
 * CoverageBinData.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: ballance
 */

#include "CoverageBinData.h"

namespace ccrt {

CoverageBinData::CoverageBinData() {
	m_hits = 0;
	m_idx = 0;
}

CoverageBinData::~CoverageBinData() {
	// TODO Auto-generated destructor stub
}

void CoverageBinData::inc() {
	m_hits++;
}

} /* namespace ccrt */
