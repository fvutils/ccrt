/*
 * RandObjCtor.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */

#include "RandObjCtor.h"
#include <stdio.h>

namespace ccrt {
RandObjCtor::RandObjCtor() {
	// TODO Auto-generated constructor stub

}

RandObjCtor::~RandObjCtor() {
	// TODO Auto-generated destructor stub
}

RandObjCtor &RandObjCtor::inst() {
	if (!m_inst) {
		m_inst = new RandObjCtor();
	}
	return *m_inst;
}

std::string RandObjCtor::auto_name() {
	fprintf(stdout, "auto_name\n");
	return "foo";
}

RandObj *RandObjCtor::scope() const {
	RandObj *ret = 0;

	for (int i=m_scope_stack.size()-1; i>=0; i--) {
		if (m_scope_stack.at(i)) {
			ret = m_scope_stack.at(i);
			break;
		}
	}

	return ret;
}

RandObj *RandObjCtor::parent() const {
	RandObj *ret = 0, *scope = 0;

	for (int i=m_scope_stack.size()-1; i>=0; i--) {
		if (m_scope_stack.at(i)) {
			if (scope) {
				ret = m_scope_stack.at(i);
			} else {
				scope = m_scope_stack.at(i);
			}
			break;
		}
	}

	return ret;
}

void RandObjCtor::enter(CtorScope *scope) {
	fprintf(stdout, "--> enter %p %p\n",
			scope->typeinfo(),
			scope->scope());
	m_scope_stack.push_back(scope->scope());

}

void RandObjCtor::leave(CtorScope *scope) {
//	m_scope_stack.pop();
	if (!scope->scope()) {
		// Pop last scopes
		RandObj *last_s = m_scope_stack.at(m_scope_stack.size()-1);

		// Remove any non-null elements
		while (m_scope_stack.size() > 0 && last_s &&
				m_scope_stack.at(m_scope_stack.size()-1) && last_s) {
			m_scope_stack.pop_back();
		}
		// Remove the null element
		if (m_scope_stack.size() > 0) {
			m_scope_stack.pop_back();
		}
	}
	fprintf(stdout, "<-- leave %p %p\n",
			scope->typeinfo(),
			scope->scope());
}

RandObjCtor *RandObjCtor::m_inst = 0;

}
