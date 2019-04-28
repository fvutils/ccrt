/*
 * CtorScope.h
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */
#pragma once
#include <string>
#include <typeinfo>
#include <stdio.h>

namespace ccrt {
class RandObj;

class CtorScope {
public:

	template <class T> CtorScope(T *s) {
		const std::type_info &ti = typeid(T);
		fprintf(stdout, "CtorScope: s=%p %p %p\n",
				s, static_cast<RandObj *>(s), dynamic_cast<RandObj *>(s));
		// Set core values
		init(0, &ti, static_cast<RandObj *>(s));
	}

	CtorScope(const char *name);

	virtual ~CtorScope();

	const std::string &name() const { return m_name; }

	const std::type_info *typeinfo() const { return m_typeinfo; }

	RandObj *scope() const { return m_scope; }

private:
	void init(
			const char 				*name,
			const std::type_info 	*ti,
			RandObj					*scope);

private:
	std::string					m_name;
	const std::type_info		*m_typeinfo;
	RandObj						*m_scope;

};

}
