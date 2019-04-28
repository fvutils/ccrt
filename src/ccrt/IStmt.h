/*
 * IStmt.h
 *
 *  Created on: Apr 6, 2019
 *      Author: ballance
 */
#pragma once
#include "boolector/boolector.h"

namespace ccrt {

class IStmt {
public:
	virtual ~IStmt() { }

	virtual BoolectorNode *build_constraint(Btor *btor) = 0;

};

}

