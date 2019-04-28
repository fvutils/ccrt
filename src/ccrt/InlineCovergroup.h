/*
 * InlineCovergroup.h
 *
 *  Created on: Apr 25, 2019
 *      Author: ballance
 */
#pragma once
#include <functional>
#include "ccrt/impl/CovergroupObj.h"
#include "CtorScope.h"

namespace ccrt {

class CovergroupModel;

class InlineCovergroup : public CovergroupObj {
public:
	InlineCovergroup(
			const CtorScope 				&scope,
			const std::function<void ()> 	&func
			);

	virtual ~InlineCovergroup();

	// Sample the containing scope of this
	void sample();

private:
	CovergroupModel						*m_model;
};

} /* namespace ccrt */
