/*
 * TestBuildConstraints.cpp
 *
 *  Created on: Apr 9, 2019
 *      Author: ballance
 */

#include "TestBuildConstraints.h"

TestBuildConstraints::TestBuildConstraints() {
	// TODO Auto-generated constructor stub

}

TestBuildConstraints::~TestBuildConstraints() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestBuildConstraints,smoke) {
	class abc : public RandObj {
	public:
		abc(const CtorScope &scope) : RandObj(this) { }

		RandVar<uint8_t>			a {"a"};
		RandVar<uint8_t>			b {"b"};
		RandVar<uint8_t>			c {"c"};
		RandVar<uint8_t>			d {"d"};

		ConstraintBuilder			abc_c { "abc_c", [this]() -> IStmt * {
			ExprBinaryOp *ret = new ExprBinaryOp(
					new ExprVarRef(a),
					ExprBinaryOp::BinOp_Lt,
					new ExprVarRef(b));
			return ret;
		}
		};
	};

	RandInst<abc>		abc_i;

	for (int i=0; i<10; i++) {
		ASSERT_TRUE(abc_i.randomize());
		fprintf(stdout, "a=%d b=%d\n", abc_i.a(), abc_i.b());
	}
}

