
#pragma once
#include <string>
#include <vector>

namespace ccrt {

class RandObj;
class Constraint;
class VarBase;
class IRandObj {
public:
	friend class VarBase;
	friend class RandObj;

	virtual ~IRandObj() { }

	virtual std::string toString() = 0;

	virtual void finalize(RandObj *root) = 0;

	virtual void set_ref(IRandObj *ref) = 0;

private:

	virtual void do_pre_randomize() = 0;

	virtual void do_post_randomize() = 0;

	virtual void get_constraints(std::vector<Constraint *> &constraints) = 0;

	virtual void get_variables(std::vector<VarBase *> &variables) = 0;

};

}
