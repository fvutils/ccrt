/*
 * TestInlineCovergroup.cpp
 *
 *  Created on: Apr 25, 2019
 *      Author: ballance
 */

#include "TestInlineCovergroup.h"


TestInlineCovergroup::TestInlineCovergroup() {
	// TODO Auto-generated constructor stub

}

TestInlineCovergroup::~TestInlineCovergroup() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestInlineCovergroup,smoke) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>				a {"a"};
		RandVar<uint8_t>				b {"b"};
		RandVar<uint8_t>				c {"c"};

		InlineCovergroup				cg {"cg", [this] {
			// TODO: need an auto-bin covergroup?
			Coverpoint				a_cp {"a_cp", a, [this] {
				Bin foo = {"foo", { {0,127} }};
				Bin bar = {"bar", { {128,255} }};
			}};

			Coverpoint				b_cp {"b_cp", b, [this] {
				Bin foo = {"foo", { {0,127} }};
				Bin bar = {"bar", { {128,255} }};
			}};

			Coverpoint				c_cp {"c_cp", c, [this] {
				Bin foo = {"foo", { {0,127} }};
				Bin bar = {"bar", { {128,255} }};
			}};

			Cross 					ab_cross {"ab_cross",
				{a_cp, b_cp, c_cp}
			};

		}};
	};

	RandInst<abc> abc_i;

	for (uint32_t i=0; i<100; i++) {
		abc_i.randomize();
		abc_i.cg.sample();
	}
}

TEST_F(TestInlineCovergroup,cross_array_rand) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>				a {"a"};
		RandVar<uint8_t>				b {"b"};

		Constraint ab_c {"ab_c", [this] {
			in(a, {{0,15}});
			in(b, {{0,15}});
		}
		};

		InlineCovergroup				cg {"cg", [this] {
			// TODO: need an auto-bin covergroup?
			Coverpoint				a_cp {"a_cp", a, [this] {
				Bins foo = {"foo", { {0,15} }};
			}};

			Coverpoint				b_cp {"b_cp", b, [this] {
				Bins foo = {"foo", { {0,15} }};
			}};

			Cross 					ab_cross {"ab_cross",
				{a_cp, b_cp}
			};

		}};
	};

	RandInst<abc> abc_i;

	for (uint32_t i=0; i<1000; i++) {
		abc_i.randomize();
		fprintf(stdout, "Value: a=%d b=%d\n",
				abc_i.a(), abc_i.b());
		abc_i.cg.sample();
	}
}

TEST_F(TestInlineCovergroup,cross_array_nonrand) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>				a {"a"};
		RandVar<uint8_t>				b {"b"};

		Constraint ab_c {"ab_c", [this] {
			in(a, {{0,15}});
			in(b, {{0,15}});
		}
		};

		InlineCovergroup				cg {"cg", [this] {
			// TODO: need an auto-bin covergroup?
			Coverpoint				a_cp {"a_cp", a, [this] {
				Bins foo = {"foo", { {0,7} }};
				Bins bar = {"bar", { {8,15} }};
			}};

			Coverpoint				b_cp {"b_cp", b, [this] {
				Bins foo = {"foo", { {0,7} }};
				Bins bar = {"bar", { {8,15} }};
			}};

			Cross 					ab_cross {"ab_cross",
				{a_cp, b_cp}
			};

		}};
	};

	RandInst<abc> abc_i;

	for (uint32_t av=0; av<=15; av++) {
		for (uint32_t bv=0; bv<=15; bv++) {
			abc_i.a() = av;
			abc_i.b() = bv;
			abc_i.cg.sample();
		}
	}
}
