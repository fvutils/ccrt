/*
 * TestCovergroup.cpp
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */

#include "TestCovergroup.h"

using namespace ccrt;

TestCovergroup::TestCovergroup() {
	// TODO Auto-generated constructor stub

}

TestCovergroup::~TestCovergroup() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestCovergroup,smoke) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>		a {"a"};
		RandVar<uint8_t>		b {"b"};
	};

	class abc_cg : public Covergroup<abc> {
	public:
		abc_cg(const CtorScope &scope) : Covergroup(this) { }

		Coverpoint				a_cp {"a_cp", a, [&] {
			Bin v1 {"v1", {1, 2, 4, 8} };
			Bin v2 {"v2", { {9,15} } };
		}
		};
	};

	RandInst<abc>		abc_i;
	abc_cg				cg {"cg"};

	cg.sample(abc_i);
}
