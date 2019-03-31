/*
 * TestBinOperators.cpp
 *
 *  Created on: Mar 30, 2019
 *      Author: ballance
 */

#include "TestBinOperators.h"

TestBinOperators::TestBinOperators() {
	// TODO Auto-generated constructor stub

}

TestBinOperators::~TestBinOperators() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestBinOperators, eq) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>			a {"a"};
		RandVar<uint8_t>			b {"b"};
		RandVar<uint8_t>			c {"c"};

		Constraint					abc_c { "abc_c", [this] {
			a == b;
			b == c;
		}
		};
	};

	RandVar<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		ASSERT_EQ(abc_i.a(), abc_i.b());
		ASSERT_EQ(abc_i.b(), abc_i.c());
	}
}

TEST_F(TestBinOperators, neq) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>			a {"a"};
		RandVar<uint8_t>			b {"b"};
		RandVar<uint8_t>			c {"c"};

		Constraint					abc_c { "abc_c", [this] {
			a != b;
			b != c;
		}
		};
	};

	RandVar<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		ASSERT_TRUE((abc_i.a() != abc_i.b()));
		ASSERT_TRUE((abc_i.b() != abc_i.c()));
	}
}

TEST_F(TestBinOperators, lt) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>			a {"a"};
		RandVar<uint8_t>			b {"b"};
		RandVar<uint8_t>			c {"c"};

		Constraint					abc_c { "abc_c", [this] {
			b < 10;
			c < 10;
			a < b;
			a < c;
		}
		};
	};

	RandVar<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		ASSERT_TRUE((abc_i.b() < 10));
		ASSERT_TRUE((abc_i.c() < 10));
		ASSERT_TRUE((abc_i.a() < (abc_i.b())));
		ASSERT_TRUE((abc_i.a() < (abc_i.c())));
	}
}

TEST_F(TestBinOperators, add) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>			a {"a"};
		RandVar<uint8_t>			b {"b"};
		RandVar<uint8_t>			c {"c"};

		Constraint					abc_c { "abc_c", [this] {
			b < 10;
			c < 10;
			a == (b + c);
		}
		};
	};

	RandVar<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		ASSERT_TRUE((abc_i.a() == (abc_i.b() + abc_i.c())));
	}
}

