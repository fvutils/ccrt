/*
 * Value.h
 *
 *  Created on: Mar 24, 2019
 *      Author: ballance
 */

#pragma once

#include <stdint.h>

namespace ccrt {
struct Value {

	union {
		uint64_t		u64;
		int64_t			s64;
		uint32_t		u32;
		int32_t			s32;
		uint16_t		u16;
		int16_t			s16;
		uint8_t			u8;
		int8_t			s8;
		bool			b;
	} val;
	bool				is_signed;
	uint32_t			bits;

	uint64_t val_u() const {
		switch (bits) {
		case 1: return val.b;
		case 8: return val.u8;
		case 16: return val.u16;
		case 32: return val.u32;
		case 64: return val.u64;
		default: return 0xdeadbeef;
		}
	}

	void val_u(uint64_t v) {
		switch (bits) {
		case 1: val.b = (v != 0); break;
		case 8: val.u8 = v; break;
		case 16: val.u16 = v; break;
		case 32: val.u32 = v; break;
		case 64: val.u64 = v; break;
		default: val.u64 = 0xdeadbeef;
		}
	}
	int64_t val_s() const {
		switch (bits) {
		case 1: return val.b;
		case 8: return val.s8;
		case 16: return val.s16;
		case 32: return val.s32;
		case 64: return val.s64;
		default: return 0xdeadbeef;
		}
	}

	void val_s(int64_t v) {
		switch (bits) {
		case 1: val.b = (v != 0); break;
		case 8: val.s8 = v; break;
		case 16: val.s16 = v; break;
		case 32: val.s32 = v; break;
		case 64: val.s64 = v; break;
		default: val.s64 = 0xdeadbeef;
		}
	}
};

}
