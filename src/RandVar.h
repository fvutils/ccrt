/*
 * RandVar.h
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */
#pragma once
#include <stdint.h>
#include "VarBase.h"
#include "RandObjCtor.h"

namespace ccrt {

template <typename T> class RandVar : public T {
public:

	// Top-level rand variable
	RandVar() : T(0) { }

	// Child element
	RandVar(const char *name) : T(name) { }

	bool randomize() {
		return static_cast<T *>(this)->do_randomize();
	}

private:


};

// TODO: Can we create a template for RandObj ?

template <> class RandVar<uint8_t> : public VarBase {
public:

	RandVar(const std::string &name=RandObjCtor::auto_name()) : VarBase(name, 8, false) { }

	uint8_t operator ()() {
		// TODO: need to map value over?
		return m_value.ui8;
	}
};

template <> class RandVar<int8_t> : public VarBase {
public:

	RandVar(const std::string &name) : VarBase(name, 8, true) { }

	int8_t operator ()() {
		// TODO: need to map value over?
		return m_value.i8;
	}
};

template <> class RandVar<uint16_t> : public VarBase {
public:

	RandVar(const std::string &name) : VarBase(name, 16, false) { }

	uint16_t operator ()() {
		// TODO: need to map value over?
		return m_value.ui16;
	}
};

// Specialization for
template <> class RandVar<uint32_t> : public VarBase {
public:

	RandVar(const std::string &name) : VarBase(name, 32, false) { }

	uint32_t operator ()() {
		// TODO: need to map value over?
		return m_value.ui32;
	}

};

// Specialization for
template <> class RandVar<int32_t> : public VarBase {
public:

	RandVar(const std::string &name) : VarBase(name, 32, true) { }

	int32_t operator ()() {
		// TODO: need to map value over?
		return m_value.i32;
	}

};

template <> class RandVar<uint64_t> : public VarBase {
public:

	RandVar(const std::string &name) : VarBase(name, 64, false) { }

	uint64_t operator ()() {
		// TODO: need to map value over?
		return m_value.ui64;
	}
};

// Specialization for
template <> class RandVar<int64_t> : public VarBase {
public:

	RandVar(const std::string &name) : VarBase(name, 64, true) { }

	int64_t operator ()() {
		// TODO: need to map value over?
		return m_value.i64;
	}
};

}
