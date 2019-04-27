/*
 * Bins.h
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */
#pragma once
#include <string>
#include <initializer_list>
#include <stdint.h>
#include "Range.h"

namespace ccrt {

class Bins {
public:
	Bins(
			const std::string 				&name,
			uint32_t 						num_bins,
			std::initializer_list<Range>	bins);

	Bins(
			const std::string 				&name,
			std::initializer_list<Range>	bins);

	virtual ~Bins();
};

} /* namespace ccrt */

