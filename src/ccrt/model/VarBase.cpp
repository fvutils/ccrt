/*
 * VarBase.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */

#include "ccrt/model/VarBase.h"

#include <stdio.h>

#include "ccrt/impl/RandObjCtor.h"
#include "ccrt/model/ExprBinaryOp.h"
#include "ccrt/model/ExprPartSelect.h"
#include "ccrt/model/ExprUnaryOp.h"
#include "ccrt/model/ExprVarRef.h"
#include "RandObj.h"

namespace ccrt {
VarBase::VarBase(
		const std::string		&name,
		uint32_t				bits,
		bool					is_signed,
		bool					is_rand) :
				m_value(bits, is_signed),
				m_name(name), m_is_rand(is_rand) {
	RandObjCtor &obj_ctor = RandObjCtor::inst();

	m_parent = obj_ctor.scope();
	m_ref = this;

	Btor *btor = obj_ctor.scope()->btor();
	BoolectorSort sort = boolector_bitvec_sort(btor, bits);
	m_node = boolector_var(btor, sort, name.c_str());

	if (obj_ctor.scope()) {
		obj_ctor.scope()->add_child(this);
	} else {
		fprintf(stdout, "Error: Var created without a parent\n");
	}
	// TODO Auto-generated constructor stub

}

VarBase::~VarBase() {
	// TODO Auto-generated destructor stub
}

std::string VarBase::toString() {
	char tmp[64];

	if (m_value.is_signed) {
		sprintf(tmp, "%lld", m_ref->m_value.val.u64);
	} else {
		sprintf(tmp, "%llu", m_ref->m_value.val.u64);
	}

	std::string ret = m_ref->m_name + " = " + tmp;

	return ret;
}

uint32_t VarBase::bits() const {
	return m_value.bits;
}

bool VarBase::is_signed() const {
	return m_value.is_signed;
}

const Value &VarBase::value() const {
	fprintf(stdout, "VarBase::value=%lld\n", m_value.val.u64);
	return m_value;
}

void VarBase::value(const Value &v) {
	// TODO: needs to respect width, etc
	m_value = v;
}

void VarBase::finalize(RandObj *root) {
	root->add_variable(this);
}

void VarBase::set_ref(IRandObj *ref) {
	if (ref) {
		m_ref = dynamic_cast<VarBase *>(ref);
	} else {
		m_ref = this;
	}
}

ConstraintBuilderExpr VarBase::operator == (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();

	IExpr *expr = new ExprBinaryOp(
					new ExprVarRef(this),
					ExprBinaryOp::BinOp_Eq,
					rhs.expr());

	return ConstraintBuilderExpr(expr);
}

ConstraintBuilderExpr VarBase::operator != (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();

	IExpr *expr = new ExprBinaryOp(
					new ExprVarRef(this),
					ExprBinaryOp::BinOp_Neq,
					rhs.expr());
	return ConstraintBuilderExpr(expr);
}

ConstraintBuilderExpr VarBase::operator + (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();

	IExpr *expr = new ExprBinaryOp(
					new ExprVarRef(this),
					ExprBinaryOp::BinOp_Add,
					rhs.expr());
	return ConstraintBuilderExpr(expr);
}

ConstraintBuilderExpr VarBase::operator - (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					new ExprVarRef(this),
					ExprBinaryOp::BinOp_Sub,
					rhs.expr()));
}

ConstraintBuilderExpr VarBase::operator & (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					new ExprVarRef(this),
					ExprBinaryOp::BinOp_And,
					rhs.expr()));
}

ConstraintBuilderExpr VarBase::operator && (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					new ExprVarRef(this),
					ExprBinaryOp::BinOp_AndAnd,
					rhs.expr()));
}

ConstraintBuilderExpr VarBase::operator | (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					new ExprVarRef(this),
					ExprBinaryOp::BinOp_Or,
					rhs.expr()));
}

ConstraintBuilderExpr VarBase::operator || (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					new ExprVarRef(this),
					ExprBinaryOp::BinOp_OrOr,
					rhs.expr()));
}

ConstraintBuilderExpr VarBase::operator ! () {

	return ConstraintBuilderExpr(new ExprUnaryOp(
					ExprUnaryOp::UnOp_Not,
					new ExprVarRef(this)));
}

ConstraintBuilderExpr VarBase::operator ~ () {

	return ConstraintBuilderExpr(new ExprUnaryOp(
					ExprUnaryOp::UnOp_Neg,
					new ExprVarRef(this)));
}

ConstraintBuilderExpr VarBase::operator < (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();

	fprintf(stdout, "VarBase: LT\n");

	return ConstraintBuilderExpr(new ExprBinaryOp(
					new ExprVarRef(this),
					ExprBinaryOp::BinOp_Lt,
					rhs.expr()));
}

ConstraintBuilderExpr VarBase::operator <= (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();

	fprintf(stdout, "VarBase: LT\n");

	return ConstraintBuilderExpr(new ExprBinaryOp(
					new ExprVarRef(this),
					ExprBinaryOp::BinOp_Le,
					rhs.expr()));
}

ConstraintBuilderExpr VarBase::operator > (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					new ExprVarRef(this),
					ExprBinaryOp::BinOp_Gt,
					rhs.expr()));
}

ConstraintBuilderExpr VarBase::operator >= (const ConstraintBuilderExpr &rhs) {
	RandObjCtor::inst().pop_expr();

	return ConstraintBuilderExpr(new ExprBinaryOp(
					new ExprVarRef(this),
					ExprBinaryOp::BinOp_Ge,
					rhs.expr()));
}

ConstraintBuilderExpr VarBase::operator [] (const Range &r) {
	return ConstraintBuilderExpr(new ExprPartSelect(
			new ExprVarRef(this), r));
}

void VarBase::do_pre_randomize() {
	// TODO: if we're not random, add in appropriate constraints
}

void VarBase::do_post_randomize() {
	const char *val = boolector_bv_assignment(m_parent->btor(), m_node);

	m_value.val.u64 = 0;

	switch (m_value.bits) {
	case 1: {
		m_value.val.b = (val[0] == '1');

	} break;
	case 8: {
		for (uint32_t i=0; i<8; i++) {
			m_value.val.u8 <<= 1;
			m_value.val.u8 |= (val[i] == '1');
		}
	} break;

	case 16: {
		for (uint32_t i=0; i<16; i++) {
			m_value.val.u16 <<= 1;
			m_value.val.u16 |= (val[i] == '1');
		}
	} break;

	case 32: {
		for (uint32_t i=0; i<32; i++) {
			m_value.val.u32 <<= 1;
			m_value.val.u32 |= (val[i] == '1');
		}
	} break;

	case 64: {
		for (uint32_t i=0; i<64; i++) {
			m_value.val.u64 <<= 1;
			m_value.val.u64 |= (val[i] == '1');
		}
	} break;
	default:
		fprintf(stdout, "Error: unknown bits %d\n", m_value.bits);
	}
}

void VarBase::get_constraints(std::vector<Constraint *> &constraints) {
	// Do nothing
	// TODO: collect a constraint for non-rand variables
}

void VarBase::get_variables(std::vector<VarBase *> &variables) {
	variables.push_back(this);
}

}
