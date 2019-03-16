/*
 * VarBase.h
 *
 *  Created on: Mar 11, 2019
 *      Author: ballance
 */
#pragma once
#include <stdint.h>
#include <string>
#include "boolector/boolector.h"

namespace ccrt {

class RandObj;

class VarBase {
public:
	VarBase(
			const std::string 	&name,
			uint32_t			bits,
			bool				is_signed);

	virtual ~VarBase();

	std::string toString();

protected:
	union val_t {
		uint64_t		ui64;
		int64_t			i64;
		uint32_t		ui32;
		int32_t			i32;
		uint16_t		ui16;
		int16_t			i16;
		uint8_t			ui8;
		int8_t			i8;
	};

	val_t				m_value;

private:
	RandObj				*m_parent;
	BoolectorNode		*m_node;
	std::string			m_name;
	uint32_t			m_bits;
	bool				m_is_signed;

};

}

