/*
 * ICoverpointBinModel.h
 *
 *  Created on: Apr 16, 2019
 *      Author: ballance
 */
#pragma once
#include <stdint.h>
#include <set>
#include "boolector/boolector.h"
#include "Value.h"

namespace ccrt {

class ICoverpointBinModel {
public:

	virtual ~ICoverpointBinModel() { }

	virtual uint32_t num_bins() const = 0;

	virtual int32_t hit_idx() const = 0;

	virtual void finalize() = 0;

	virtual void sample(const Value &v) = 0;

	/**
	 * Builds a bin constraint for a specific bin
	 */
	virtual BoolectorNode *bin_constraint(uint32_t bin_idx) = 0;

//	virtual std::set<uint32_t> unhit_bins();

};

}
