/*
 * RandVar.h
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */
#pragma once
#include <stdint.h>

#include "impl/RandObjCtor.h"
#include "model/VarBase.h"

namespace ccrt {

template <typename T> class RandVar : public T {
public:

	// Top-level rand variable
	RandVar() : T(0) { }

	// Child element
	RandVar(const char *name) : T(name) { }

private:


};

// TODO: Can we create a template for RandObj ?

template <> class RandVar<bool> : public VarBase {
public:

	RandVar(const std::string &name=RandObjCtor::auto_name()) : VarBase(name, 1, false, true) { }

	bool operator ()() {
		// TODO: need to map value over?
		return m_value.val.b;
	}

//	ConstraintBuilderExpr operator == (const ConstraintBuilderExpr &rhs) {
//		return VarBase::operator == (rhs);
//	}
//
//	ConstraintBuilderExpr operator != (const ConstraintBuilderExpr &rhs) {
//		return VarBase::operator != (rhs);
//	}
//
//	ConstraintBuilderExpr operator && (const ConstraintBuilderExpr &rhs) {
//		return VarBase::operator && (rhs);
//	}

//	bool operator == (const VarBase &rhs) {
//		return RandObjCtor::mkEq(*this, rhs);
//	}
};

template <> class RandVar<uint8_t> : public VarBase {
public:

	RandVar(const std::string &name=RandObjCtor::auto_name()) : VarBase(name, 8, false, true) { }

	uint8_t operator ()() {
		// TODO: need to map value over?
		return m_value.val.u8;
	}

//	ConstraintBuilderExpr operator == (const ConstraintBuilderExpr &rhs) {
//		return VarBase::operator == (rhs);
//	}
//
//	ConstraintBuilderExpr operator != (const ConstraintBuilderExpr &rhs) {
//		return VarBase::operator != (rhs);
//	}
//
//	ConstraintBuilderExpr operator && (const ConstraintBuilderExpr &rhs) {
//		return VarBase::operator && (rhs);
//	}

//	bool operator == (const VarBase &rhs) {
//		return RandObjCtor::mkEq(*this, rhs);
//	}
};

template <> class RandVar<int8_t> : public VarBase {
public:

	RandVar(const std::string &name) : VarBase(name, 8, true, true) { }

	int8_t operator ()() {
		// TODO: need to map value over?
		return m_value.val.s8;
	}
};

template <> class RandVar<uint16_t> : public VarBase {
public:

	RandVar(const std::string &name) : VarBase(name, 16, false, true) { }

	uint16_t operator ()() {
		// TODO: need to map value over?
		return m_value.val.u16;
	}
};

// Specialization for
template <> class RandVar<uint32_t> : public VarBase {
public:

	RandVar(const std::string &name) : VarBase(name, 32, false, true) { }

	uint32_t operator ()() {
		// TODO: need to map value over?
		return m_value.val.u32;
	}

};

// Specialization for
template <> class RandVar<int32_t> : public VarBase {
public:

	RandVar(const std::string &name) : VarBase(name, 32, true, true) { }

	int32_t operator ()() {
		// TODO: need to map value over?
		return m_value.val.s32;
	}

};

template <> class RandVar<uint64_t> : public VarBase {
public:

	RandVar(const std::string &name) : VarBase(name, 64, false, true) { }

	uint64_t operator ()() {
		// TODO: need to map value over?
		return m_value.val.u64;
	}
};

// Specialization for
template <> class RandVar<int64_t> : public VarBase {
public:

	RandVar(const std::string &name) : VarBase(name, 64, true, true) { }

	int64_t operator ()() {
		// TODO: need to map value over?
		return m_value.val.s64;
	}
};

}
