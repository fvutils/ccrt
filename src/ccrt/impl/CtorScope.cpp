/*
 * CtorScope.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */

#include "CtorScope.h"
#include "RandObj.h"
#include <stdio.h>
#include "ccrt/impl/RandObjCtor.h"

namespace ccrt {

CtorScope::CtorScope(const char *name) {
	fprintf(stdout, "CtorScope: name=%s\n", name);
	init(name, 0, 0);
}

CtorScope::~CtorScope() {
	RandObjCtor::inst().leave(this);
	// TODO Auto-generated destructor stub
}

void CtorScope::init(
		const char 				*name,
		const std::type_info 	*ti,
		RandObj					*scope) {
	m_name = (name)?name:"name-null";
	m_typeinfo = ti;
	m_scope = scope;

	RandObjCtor::inst().enter(this);
}

}

