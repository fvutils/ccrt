/*
 * RandObjCtor.h
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */
#pragma once
#include <stack>
#include <vector>
#include "RandObj.h"

namespace ccrt {

class CtorScope;

class RandObjCtor {
public:
	friend class CtorScope;
	RandObjCtor();

	virtual ~RandObjCtor();

	static RandObjCtor &inst();

	static std::string auto_name();

	RandObj *scope() const;

	RandObj *parent() const;

private:

	void enter(CtorScope *scope);

	void leave(CtorScope *scope);


private:
	std::vector<RandObj *>			m_scope_stack;
//	std::stack<CtorScope>			m_scope_stack;
//	std::stack<RandObj *>			m_scope_stack;
	static RandObjCtor				*m_inst;
};

}
