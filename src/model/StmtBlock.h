/*
 * StmtBlock.h
 *
 *  Created on: Apr 7, 2019
 *      Author: ballance
 */
#pragma once
#include "IStmt.h"
#include <vector>
#include "model/StmtBase.h"

namespace ccrt {

class StmtBlock : public StmtBase {
public:
	StmtBlock(const std::vector<IStmt *> &stmts);

	virtual ~StmtBlock();

	const std::vector<IStmt *> &stmts() const { return m_stmts; }

	virtual BoolectorNode *build_constraint(Btor *btor);

private:
	std::vector<IStmt *>			m_stmts;

};

} /* namespace ccrt */

