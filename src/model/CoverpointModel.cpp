/*
 * CoverpointModel.cpp
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */

#include "model/CoverpointModel.h"

#include <string.h>

namespace ccrt {

CoverpointModel::CoverpointModel(
		const std::string 	&name,
		IExpr				*expr) : m_name(name), m_expr(expr) {
	// TODO Auto-generated constructor stub

}

CoverpointModel::~CoverpointModel() {
	// TODO Auto-generated destructor stub
}

int32_t CoverpointModel::hit_bin() {
	return m_hit_bin;
}

void CoverpointModel::add_bin(ICoverpointBinModel *bin) {
	m_bins.push_back(bin);
}

void CoverpointModel::finalize() {
	m_n_bins = 0;

	// First, finalize all the bins
	for (std::vector<ICoverpointBinModel *>::const_iterator it=m_bins.begin();
			it!=m_bins.end(); it++) {
		(*it)->finalize();
	}

	// Determine how many bins we have
	for (std::vector<ICoverpointBinModel *>::const_iterator it=m_bins.begin();
			it!=m_bins.end(); it++) {
		m_n_bins += (*it)->num_bins();
	}

	// Fill up the unhit bins set
	for (uint32_t i=0; i<m_n_bins; i++) {
		m_unhit_bins.insert(i);
	}

	// Create an initialize the bin-data array
	m_bin_data = new uint32_t[m_n_bins];
	memset(m_bin_data, 0, sizeof(uint32_t)*m_n_bins);
}

void CoverpointModel::sample() {
	Value v = m_expr->value();
	uint32_t idx = 0;

	fprintf(stdout, "sample: v=%lld\n", v.val_u());

	for (std::vector<ICoverpointBinModel *>::iterator it=m_bins.begin();
			it!=m_bins.end(); it++) {
		(*it)->sample(v);

		if ((*it)->hit_idx() != -1) {
			m_bin_data[idx+(*it)->hit_idx()]++;
			fprintf(stdout, "Note: bin hit => %d\n",
					m_bin_data[idx+(*it)->hit_idx()]);
		}

		idx += (*it)->num_bins();
	}
}

} /* namespace ccrt */
