/*
 * RandInst.h
 *
 *  Created on: Apr 7, 2019
 *      Author: ballance
 */
#pragma once
#include "RandObj.h"
#include "RandObjCtor.h"
#include <functional>

namespace ccrt {
template <class T> class RandInst : public T {
public:

	RandInst() : T(0) {

	}

	bool randomize() {
		return static_cast<T *>(this)->do_randomize();
	}

	bool randomize(const std::function<void ()> &with) {
		uint32_t pre_size = RandObjCtor::inst().get_expressions().size();
		Btor *btor = static_cast<T *>(this)->btor();
		with();
		std::vector <IStmt *> stmts = RandObjCtor::inst().truncate_expressions(pre_size);

		// Add the constraints (if any) to the randomization
		BoolectorNode *with_c = 0;

		for (std::vector<IStmt *>::const_iterator it=stmts.begin();
				it!=stmts.end(); it++) {
			if (with_c) {
				with_c = boolector_and(btor,
						with_c,
						(*it)->build_constraint(btor));
			} else {
				with_c = (*it)->build_constraint(btor);
			}
		}

		bool ret = static_cast<T *>(this)->do_randomize(with_c);

		// TODO: clean up after stmts
		// TODO: release inline constraints

		return ret;
	}
};

}
