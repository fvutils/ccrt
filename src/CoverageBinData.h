/*
 * CoverageBinData.h
 *
 *  Created on: Apr 16, 2019
 *      Author: ballance
 */
#pragma once
#include <stdint.h>

namespace ccrt {

class CoverageBinData {
public:
	CoverageBinData();

	virtual ~CoverageBinData();

	uint32_t idx() const { return m_idx; }

	void idx(uint32_t idx) { m_idx = idx; }

	uint32_t hits() const { return m_hits; }

	void inc();

private:
	uint32_t			m_idx;
	uint32_t			m_hits;

};

} /* namespace ccrt */

