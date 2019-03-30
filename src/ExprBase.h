/*
 * ExprBase.h
 *
 *  Created on: Mar 23, 2019
 *      Author: ballance
 */

#pragma once
#include <stdint.h>
#include <memory>
#include "IExpr.h"

namespace ccrt {

class ExprBase : public virtual IExpr {
public:
	ExprBase(uint32_t bits, bool is_signed);

	virtual ~ExprBase();

	virtual bool is_signed() const { return m_is_signed; }

	virtual uint32_t bits() const { return m_bits; }

protected:

	static void resize(
			Btor			*btor,
			IExpr			*v1,
			IExpr			*v2,
			BoolectorNode	**v1_n,
			BoolectorNode	**v2_n,
			bool			*is_signed
			);

protected:
	uint32_t				m_bits;
	bool					m_is_signed;


};

} /* namespace ccrt */
