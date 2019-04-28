/*
 * StmtBase.h
 *
 *  Created on: Apr 6, 2019
 *      Author: ballance
 */
#pragma once
#include "ccrt/IStmt.h"

namespace ccrt {

class StmtBase : public virtual IStmt {
public:
	StmtBase();

	virtual ~StmtBase();

};

} /* namespace ccrt */

