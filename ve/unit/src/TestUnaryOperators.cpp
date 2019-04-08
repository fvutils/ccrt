/*
 * TestUnaryOperators.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: ballance
 */

#include "TestUnaryOperators.h"

TestUnaryOperators::TestUnaryOperators() {
	// TODO Auto-generated constructor stub

}

TestUnaryOperators::~TestUnaryOperators() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestUnaryOperators,part_select1) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t> 		a {"a"};
		RandVar<uint8_t>		b {"b"};

		Constraint abc_c {"abc_c", [this] {
				a == b[3];
			}
		};
	};

	RandInst<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		fprintf(stdout, "a=%02x b=%02x\n", abc_i.a(), abc_i.b());
		ASSERT_EQ(abc_i.a(), ((abc_i.b() & 0x8) >> 3));
	}
}

TEST_F(TestUnaryOperators,part_select2) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t> 		a {"a"};
		RandVar<uint8_t>		b {"b"};

		Constraint abc_c {"abc_c", [this] {
				a == b[R(3,2)];
			}
		};
	};

	RandInst<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		fprintf(stdout, "a=%02x b=%02x\n", abc_i.a(), abc_i.b());
		ASSERT_EQ(abc_i.a(), ((abc_i.b() & 0xC) >> 2));
	}
}

TEST_F(TestUnaryOperators,not) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t> 		a {"a"};
		RandVar<uint8_t>		b {"b"};

		Constraint abc_c {"abc_c", [this] {
				a == !b;
			}
		};
	};

	RandInst<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		fprintf(stdout, "a=%02x b=%02x\n", abc_i.a(), abc_i.b());
		ASSERT_TRUE((abc_i.a() == (abc_i.b())?0:1));
	}
}

TEST_F(TestUnaryOperators,neg) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t> 		a {"a"};
		RandVar<uint8_t>		b {"b"};

		Constraint abc_c {"abc_c", [this] {
				a == ~b;
			}
		};
	};

	RandInst<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		fprintf(stdout, "a=%02x b=%02x\n", abc_i.a(), abc_i.b());
		uint8_t a = abc_i.a();
		uint8_t b = abc_i.b();
		uint8_t c = ~b;
		fprintf(stdout, "  a=%02x b=%02x c=%02x\n", a, b, c);
		ASSERT_TRUE((a == c));
	}
}



