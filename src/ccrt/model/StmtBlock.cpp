/*
 * StmtBlock.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: ballance
 */

#include "ccrt/model/StmtBlock.h"

namespace ccrt {

StmtBlock::StmtBlock(const std::vector<IStmt *> &stmts) :
	m_stmts(stmts) {
	// TODO Auto-generated constructor stub

}

StmtBlock::~StmtBlock() {
	// TODO Auto-generated destructor stub
}

BoolectorNode *StmtBlock::build_constraint(Btor *btor) {
	BoolectorNode *ret = 0;

	for (std::vector<IStmt *>::const_iterator it=m_stmts.begin();
			it!=m_stmts.end(); it++) {
		if (ret) {
			ret = boolector_and(
					btor,
					ret,
					(*it)->build_constraint(btor)
			);
		} else {
			ret = (*it)->build_constraint(btor);
		}
	}

	if (!ret) {
		// empty block. Return a generic 'true'
		ret = boolector_one(btor, boolector_bitvec_sort(btor, 1));
	}

	return ret;
}

} /* namespace ccrt */
