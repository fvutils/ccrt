/*
 * InlineCovergroup.cpp
 *
 *  Created on: Apr 25, 2019
 *      Author: ballance
 */

#include "InlineCovergroup.h"
#include "model/CovergroupModel.h"
#include "impl/RandObjCtor.h"

namespace ccrt {

InlineCovergroup::InlineCovergroup(
		const CtorScope 				&scope,
		const std::function<void ()>	&func) : CovergroupObj(0) {
	// TODO: need to obtain the handle of the parent
	RandObj *sample_it = RandObjCtor::inst().scope(); // TODO: obtain and validate the parent handle
	fprintf(stdout, "sample_it=%p\n", sample_it);

	m_model = new CovergroupModel(sample_it);

	// Construct the items
	// Set the covergroup context to receive the component items
	RandObjCtor::inst().set_covergroup_ctxt(m_model);
	func();
	RandObjCtor::inst().set_covergroup_ctxt(0);

	m_model->finalize();
}

InlineCovergroup::~InlineCovergroup() {
	// TODO Auto-generated destructor stub
}

void InlineCovergroup::sample() {
	// Sample using the original object type
	m_model->sample();
}

} /* namespace ccrt */
