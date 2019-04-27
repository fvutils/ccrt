/*
 * CovergroupModel.h
 *
 *  Created on: Apr 25, 2019
 *      Author: ballance
 */
#pragma once
#include <vector>
#include "RandObj.h"
#include "model/CoverpointModel.h"
#include "model/CoverpointCrossModel.h"

namespace ccrt {

class CovergroupModel {
public:

	// The sample item is the object on which coverpoints are declared
	CovergroupModel(RandObj *sample_it);

	virtual ~CovergroupModel();

	virtual void finalize();

	virtual void sample(RandObj *t=0);

	void add_coverpoint(CoverpointModel *cp);

	void add_crosspoint(CoverpointCrossModel *cross);

private:
	RandObj									*m_sample_it;
	std::vector<CoverpointModel *>			m_coverpoints;
	std::vector<CoverpointCrossModel *>		m_crosspoints;

};

} /* namespace ccrt */

