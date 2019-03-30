/*
 * IExpr.h
 *
 *  Created on: Mar 23, 2019
 *      Author: ballance
 */

#pragma once
#include "boolector/boolector.h"
#include "Value.h"
#include <stdint.h>

namespace ccrt {

class IExpr {
public:
	virtual ~IExpr() { }

	virtual Value value() = 0;

	virtual BoolectorNode *build_constraint(Btor *btor) = 0;

	virtual bool is_signed() const = 0;

	virtual uint32_t bits() const = 0;

};

}
