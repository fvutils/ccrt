/*
 * CoverpointCrossModel.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: ballance
 */

#include "model/CoverpointCrossModel.h"

#include "CoverageBinData.h"
#include "model/ICoverpointBinModel.h"
#include "model/CoverpointModel.h"

namespace ccrt {

CoverpointCrossModel::CoverpointCrossModel() {
	// TODO Auto-generated constructor stub

}

CoverpointCrossModel::~CoverpointCrossModel() {
	// TODO Auto-generated destructor stub
}

void CoverpointCrossModel::add_coverpoint(CoverpointModel *cp) {
	m_coverpoints.push_back(cp);
}

void CoverpointCrossModel::finalize() {

	fprintf(stdout, "--> finalize\n");

	for (uint32_t i=1; i<m_coverpoints.size(); i++) {
		m_coverpoint_scale_factors.push_back(0);
	}

	uint32_t total_bins = 1;
	for (uint32_t cp_idx=0; cp_idx<m_coverpoints.size(); cp_idx++) {
		CoverpointModel *cp = m_coverpoints.at(cp_idx);
		uint32_t bins_per_coverpoint = 0;
		for (std::vector<ICoverpointBinModel *>::const_iterator b_it=cp->bins().begin();
				b_it!=cp->bins().end(); b_it++) {
			bins_per_coverpoint += (*b_it)->num_bins();
		}
		if (bins_per_coverpoint > 0) {
			total_bins *= bins_per_coverpoint;
			if (cp_idx+1 < m_coverpoints.size()) {
				m_coverpoint_scale_factors.at(m_coverpoints.size()-cp_idx-2) = total_bins;
			}
		} else {
			fprintf(stdout, "Warning: zero bins specified\n");
		}
	}

	fprintf(stdout, "Cross: total_bins=%d\n", total_bins);

	for (uint32_t i=0; i<m_coverpoint_scale_factors.size(); i++) {
		fprintf(stdout, "scale[%d] = %d\n", i, m_coverpoint_scale_factors.at(i));
	}

	m_bin_data = new CoverageBinData[total_bins];
	m_bin_data_len = total_bins;

	// Add a 'unhit bin' for each
	for (uint32_t i=0; i<total_bins; i++) {
		m_bin_data[i].idx(i);
		m_unhit_bins.emplace(i);
	}
	fprintf(stdout, "<-- finalize\n");
}

void CoverpointCrossModel::sample() {
	int32_t idx = -1;

	// idx needs to increment by bin-based step each time
	//

	// Need combinations of all bin sets:
	// cp0.bin0, {cp1.bin0, cp1.bin1}
	// Need a tree
	std::vector<uint32_t> bin_idx_l;
	sample(0, bin_idx_l);
}

void CoverpointCrossModel::sample(
		uint32_t					cp_idx,
		const std::vector<uint32_t> &bin_idx_l) {

//	fprintf(stdout, "--> sample(%d)\n", cp_idx);

	if (cp_idx+1 >= m_coverpoints.size()) {
		CoverpointModel *cp = m_coverpoints.at(cp_idx);
//		std::vector<uint32_t> bin_idx_n_l = bin_idx_l;
//		bin_idx_n_l.push_back(0);

		for (uint32_t i=0; i<cp->bins().size(); i++) {
			if (cp->bins().at(i)->hit_idx() != -1) {
				uint32_t idx = 0;

				for (uint32_t si=0; si<bin_idx_l.size(); si++) {
					idx += m_coverpoint_scale_factors.at(si)*bin_idx_l.at(si);
				}

				idx += i;

				m_bin_data[idx].inc();
				fprintf(stdout, "Hit: idx=%d hits=%d\n",
						idx, m_bin_data[idx].hits());

//				fprintf(stdout, "Hits: ");
//				for (uint32_t x=0; x<m_bin_data_len; x++) {
//					fprintf(stdout, "%d ", m_bin_data[x].hits());
//				}
//				fprintf(stdout, "\n");

//				bin_idx_n_l.at(bin_idx_l.size()) = i;
//				fprintf(stdout, "TODO: sample - idx=%d\n", idx);
//				fprintf(stdout, "    ");
//				for (uint32_t i=0; i<bin_idx_l.size(); i++) {
//					fprintf(stdout, "%d ", bin_idx_l.at(i));
//				}
//				fprintf(stdout, "\n");
			}
		}
	} else {
		std::vector<uint32_t> bin_idx_n_l = bin_idx_l;
		CoverpointModel *cp = m_coverpoints.at(cp_idx);

		bin_idx_n_l.push_back(0);

		for (uint32_t i=0; i<cp->bins().size(); i++) {
			if (cp->bins().at(i)->hit_idx() != -1) {
				bin_idx_n_l.at(bin_idx_l.size()) = i;
				sample(cp_idx+1, bin_idx_n_l);
			}
		}
	}


//	// Start with cp[x] ;
//	// Need to explore all bins with all cp[x+1]
//
//	CoverpointModel *cp = m_coverpoints.at(cp_idx);
//
//	// Determine whether this bin is hit
//	int32_t hit_idx = m_coverpoints.at(cp_idx)->bins().at(bin_idx)->hit_idx();
//
//	if (hit_idx != -1) {
//		// The initial bin is hit
//
//		if (cp_idx+1 < m_coverpoints.size()) {
//			CoverpointModel *cp_n = m_coverpoints.at(cp_idx+1);
//
//			// Recurse
//			for (uint32_t i=0; i<cp_n->bins().size(); i++) {
//				// Need to recurse into all coverpoints cp_idx+1
//				// TODO: determine how to manipulate idx
//				sample(idx, cp_idx+1, i);
//			}
//		} else {
//			// We are ready to sample
//			fprintf(stdout, "Note: sample idx=%d\n", (idx+hit_idx));
//		}
//	}
//	fprintf(stdout, "<-- sample(%d)\n", cp_idx);
}

} /* namespace ccrt */
