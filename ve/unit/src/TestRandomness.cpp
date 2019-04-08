/*
 * TestRandomness.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: ballance
 */

#include "TestRandomness.h"

TestRandomness::TestRandomness() {
	// TODO Auto-generated constructor stub

}

TestRandomness::~TestRandomness() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestRandomness, singlevar) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>		a {"a"};
	};

	RandInst<abc>		abc_i;
	uint8_t				bins[256];

	for (int i=0; i<256; i++) {
		bins[i] = 0;
	}

	for (int i=0; i<256*4; i++) {
		ASSERT_TRUE(abc_i.randomize());
		bins[abc_i.a()]++;
	}

	uint32_t n_hit = 0;
	for (int i=0; i<256; i++) {
		fprintf(stdout, "bins[%d] = %d\n", i, bins[i]);
		if (bins[i]) {
			n_hit++;
		}
	}

	fprintf(stdout, "TestRandomness: n_hit=%d\n", n_hit);
}

TEST_F(TestRandomness, twovar) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>		a {"a"};
		RandVar<uint8_t>		b {"b"};
	};

	RandInst<abc>		abc_i;
	uint8_t				bins_a[256];
	uint8_t				bins_b[256];

	for (int i=0; i<256; i++) {
		bins_a[i] = 0;
		bins_b[i] = 0;
	}

	for (int i=0; i<256*4; i++) {
		ASSERT_TRUE(abc_i.randomize());
		bins_a[abc_i.a()]++;
		bins_b[abc_i.b()]++;
	}

	uint32_t n_hit_a = 0;
	uint32_t n_hit_b = 0;
	for (int i=0; i<256; i++) {
		fprintf(stdout, "bins[%d] a=%d b=%d\n", i, bins_a[i], bins_b[i]);
		if (bins_a[i]) {
			n_hit_a++;
		}
		if (bins_b[i]) {
			n_hit_b++;
		}
	}

	fprintf(stdout, "TestRandomness: n_hit_a=%d n_hit_b=%d\n", n_hit_a, n_hit_b);
}
