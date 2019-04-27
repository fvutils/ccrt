/*
 * CovergroupObj.h
 *
 *  Created on: Apr 21, 2019
 *      Author: ballance
 */

#pragma once

namespace ccrt {

class RandObj;

class CovergroupObj {
public:
	CovergroupObj(RandObj *it);

	virtual ~CovergroupObj();

	void do_sample(RandObj *t);

private:
	RandObj					*m_sample_it;
};

} /* namespace ccrt */

