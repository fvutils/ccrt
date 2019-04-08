/*
 * TestConstraintStmts.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: ballance
 */

#include "TestConstraintStmts.h"

using namespace ccrt;

TestConstraintStmts::TestConstraintStmts() {
	// TODO Auto-generated constructor stub

}

TestConstraintStmts::~TestConstraintStmts() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestConstraintStmts, implies) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>			a {"a"};
		RandVar<uint8_t>			b {"b"};
		RandVar<uint8_t>			c {"c"};
		RandVar<uint8_t>			d {"d"};

		Constraint					abc_c { "abc_c", [this] {
			implies(a < 10, [this] {
				c == d;
			});
			implies(a > 10, [this] {
				c != d;
			});
		}
		};
	};

	RandInst<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		if (abc_i.a() < 10) {
			ASSERT_TRUE((abc_i.c() == abc_i.d()));
		} else {
			ASSERT_TRUE((abc_i.c() != abc_i.d()));
		}
	}
}

TEST_F(TestConstraintStmts, if_then) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>			a {"a"};
		RandVar<uint8_t>			b {"b"};
		RandVar<uint8_t>			c {"c"};
		RandVar<uint8_t>			d {"d"};

		Constraint					abc_c { "abc_c", [this] {
			if_then(a < 10, [this] {
				c == d;
			});
			if_then(a > 10, [this] {
				c != d;
			});
		}
		};
	};

	RandInst<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		if (abc_i.a() < 10) {
			ASSERT_TRUE((abc_i.c() == abc_i.d()));
		} else {
			ASSERT_TRUE((abc_i.c() != abc_i.d()));
		}
	}
}

TEST_F(TestConstraintStmts, if_then_else) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>			a {"a"};
		RandVar<uint8_t>			b {"b"};
		RandVar<uint8_t>			c {"c"};
		RandVar<uint8_t>			d {"d"};

		Constraint					abc_c { "abc_c", [this] {
			if_then(a < 10, [this] {
				c == d;
			}).else_then([this] {
				c != d;
			});
		}
		};
	};

	RandInst<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		if (abc_i.a() < 10) {
			ASSERT_TRUE((abc_i.c() == abc_i.d()));
		} else {
			ASSERT_TRUE((abc_i.c() != abc_i.d()));
		}
	}
}

TEST_F(TestConstraintStmts, if_then_else_nested) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>			a {"a"};
		RandVar<uint8_t>			b {"b"};
		RandVar<uint8_t>			c {"c"};
		RandVar<uint8_t>			d {"d"};

		Constraint					abc_c { "abc_c", [this] {
			if_then(a < 10, [this] {
				if_then(a == 5, [this] {
					c == 5;
					d == 10;
				}).else_then([this] {
					c == 6;
					d == 11;
				});
			}).else_then([this] {
				c == d;
			});
		}
		};
	};

	RandInst<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		fprintf(stdout, "a=%d b=%d c=%d d=%d\n",
				abc_i.a(), abc_i.b(), abc_i.c(), abc_i.d());
		if (abc_i.a() < 10) {
			if (abc_i.a() == 5) {
				ASSERT_TRUE((abc_i.c() == 5));
				ASSERT_TRUE((abc_i.d() == 10));
			} else {
				ASSERT_TRUE((abc_i.c() == 6));
				ASSERT_TRUE((abc_i.d() == 11));
			}
		} else {
			ASSERT_TRUE((abc_i.c() == abc_i.d()));
		}
	}
}

TEST_F(TestConstraintStmts, randomize_with) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>			a {"a"};
		RandVar<uint8_t>			b {"b"};
		RandVar<uint8_t>			c {"c"};
		RandVar<uint8_t>			d {"d"};

		Constraint					abc_c { "abc_c", [this] {
			if_then(a < 10, [&] {
				if_then(a == 5, [&] {
					c == 5;
					d == 10;
				}).else_then([&] {
					c == 6;
					d == 11;
				});
			}).else_then([&] {
				c == d;
			});
		}
		};
	};

	RandInst<abc>		abc_i;

	for (int i=0; i<20; i++) {
		ASSERT_TRUE(abc_i.randomize([&] {
			abc_i.a == i;
		}));
		fprintf(stdout, "a=%d b=%d c=%d d=%d\n",
				abc_i.a(), abc_i.b(), abc_i.c(), abc_i.d());
		if (abc_i.a() < 10) {
			if (abc_i.a() == 5) {
				ASSERT_TRUE((abc_i.c() == 5));
				ASSERT_TRUE((abc_i.d() == 10));
			} else {
				ASSERT_TRUE((abc_i.c() == 6));
				ASSERT_TRUE((abc_i.d() == 11));
			}
		} else {
			ASSERT_TRUE((abc_i.c() == abc_i.d()));
		}
	}
}


