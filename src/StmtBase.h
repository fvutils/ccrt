/*
 * StmtBase.h
 *
 *  Created on: Apr 6, 2019
 *      Author: ballance
 */
#pragma once
#include "IStmt.h"

namespace ccrt {

class StmtBase : public virtual IStmt {
public:
	StmtBase();

	virtual ~StmtBase();

};

} /* namespace ccrt */

