/*
 * Range.h
 *
 *  Created on: Apr 1, 2019
 *      Author: ballance
 */

#pragma once
#include <stdint.h>

namespace ccrt {

class Range {
public:
	Range(uint32_t lhs, uint32_t rhs) : m_rhs(rhs), m_lhs(lhs) { }

	Range(uint32_t bit) : m_rhs(bit), m_lhs(bit) { }

	uint32_t rhs() const { return m_rhs; }

	uint32_t lhs() const { return m_lhs; }

	virtual ~Range();

private:
	uint32_t			m_rhs;
	uint32_t			m_lhs;
};

typedef Range R;

} /* namespace ccrt */

