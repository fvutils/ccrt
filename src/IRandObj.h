
#pragma once
#include <string>

namespace ccrt {

class RandObj;
class IRandObj {
public:
	friend class VarBase;
	friend class RandObj;

	virtual ~IRandObj() { }

	virtual std::string toString() = 0;

	virtual void finalize(RandObj *root) = 0;

private:

	virtual void do_pre_randomize() = 0;

	virtual void do_post_randomize() = 0;

};

}
