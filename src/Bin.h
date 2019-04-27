/*
 * Bin.h
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */
#pragma once
#include <string>
#include <initializer_list>
#include "Range.h"

namespace ccrt {

class CoverpointSingleBinModel;

class Bin {
public:
	Bin(
			const std::string 				&name,
			std::initializer_list<Range>	bins);

	virtual ~Bin();

private:

	CoverpointSingleBinModel				*m_model;
};

} /* namespace ccrt */

