/*
 * TestInOperator.cpp
 *
 *  Created on: Apr 12, 2019
 *      Author: ballance
 */

#include "TestInOperator.h"

TestInOperator::TestInOperator() {
	// TODO Auto-generated constructor stub

}

TestInOperator::~TestInOperator() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestInOperator, single_range_1) {

	class abc : public RandObj {
	public:
		abc(const CtorScope &s) : RandObj(this) {

		}

		RandVar<uint8_t>			a {"a"};
		RandVar<uint8_t>			b {"b"};

		Constraint c {"c", [this] {
			in(a, { {1,100} });
		}
		};
	};

	RandInst<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		ASSERT_TRUE(abc_i.a() >= 1 && abc_i.a() <= 100);
	}
}

TEST_F(TestInOperator, multi_values) {

	class abc : public RandObj {
	public:
		abc(const CtorScope &s) : RandObj(this) {

		}

		RandVar<uint8_t>			a {"a"};

		Constraint c {"c", [this] {
			in(a, { 1, 3, 5, 7 });
		}
		};
	};

	RandInst<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		ASSERT_TRUE(
				abc_i.a() == 1 ||
				abc_i.a() == 3 ||
				abc_i.a() == 5 ||
				abc_i.a() == 7);
	}
}
