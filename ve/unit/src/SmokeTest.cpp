/*
 * SmokeTest.cpp
 *
 *  Created on: Mar 30, 2019
 *      Author: ballance
 */

#include "SmokeTest.h"
#include "ccrt/ccrt.h"

using namespace ccrt;

SmokeTest::SmokeTest() {
	// TODO Auto-generated constructor stub

}

SmokeTest::~SmokeTest() {
	// TODO Auto-generated destructor stub
}



TEST_F(SmokeTest, basic) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>		a {"a"};
		RandVar<uint8_t>		b {"b"};
		RandVar<uint8_t>		c {"c"};

		Constraint				abc_c { "abc_c", [this] {
				a != b;
				b != c;
			}
		};
	};

	RandInst<abc>			abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		ASSERT_TRUE(abc_i.a() != abc_i.b());
		ASSERT_TRUE(abc_i.b() != abc_i.c());
	}
}
