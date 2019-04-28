/*
 * CovergroupModel.cpp
 *
 *  Created on: Apr 25, 2019
 *      Author: ballance
 */

#include "CovergroupModel.h"

namespace ccrt {

CovergroupModel::CovergroupModel(RandObj *sample_it) : m_sample_it(sample_it) {
	// TODO Auto-generated constructor stub

}

CovergroupModel::~CovergroupModel() {
	// TODO Auto-generated destructor stub
}

void CovergroupModel::finalize() {
	for (std::vector<CoverpointModel *>::const_iterator it=m_coverpoints.begin();
			it!=m_coverpoints.end(); it++) {
		(*it)->finalize();
	}
	for (std::vector<CoverpointCrossModel *>::const_iterator it=m_crosspoints.begin();
			it!=m_crosspoints.end(); it++) {
		(*it)->finalize();
	}
}

void CovergroupModel::sample(RandObj *t) {
	// set actual item to sample
	fprintf(stdout, "sample: t=%p sample_it=%p\n", t, m_sample_it);
	if (t == m_sample_it) {
		m_sample_it->set_ref(0);
	} else {
		m_sample_it->set_ref(t);
	}

	// Sample coverpoints first
	for (std::vector<CoverpointModel *>::const_iterator it=m_coverpoints.begin();
			it!=m_coverpoints.end(); it++) {
		(*it)->sample();
	}
	// Next, crosspoints
	for (std::vector<CoverpointCrossModel *>::const_iterator it=m_crosspoints.begin();
			it!=m_crosspoints.end(); it++) {
		(*it)->sample();
	}
}

void CovergroupModel::add_coverpoint(CoverpointModel *cp) {
	m_coverpoints.push_back(cp);
}

void CovergroupModel::add_crosspoint(CoverpointCrossModel *cross) {
	m_crosspoints.push_back(cross);
}

} /* namespace ccrt */
