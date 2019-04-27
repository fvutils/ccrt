/*
 * CoverpointModel.h
 *
 *  Created on: Apr 14, 2019
 *      Author: ballance
 */

#include <string>
#include <vector>
#include <map>
#include <stdint.h>

#include "ICoverpointBinModel.h"
#include "IExpr.h"

namespace ccrt {
class CoverpointBinGroup;

class CoverpointModel {
public:
	CoverpointModel(
			const std::string 	&name,
			IExpr				*expr);

	virtual ~CoverpointModel();

//	virtual void do_sample();

	int32_t hit_bin();

	void add_bin(ICoverpointBinModel *bin);

	const std::vector<ICoverpointBinModel *> &bins() const {
		return m_bins;
	}

	const std::set<uint32_t> &unhit_bins() const {
		return m_unhit_bins;
	}

	const std::set<uint32_t> &unreachable_bins() const {
		return m_unreachable_bins;
	}

	void finalize();

	void sample();

private:
	std::string										m_name;
	IExpr											*m_expr;
	std::vector<ICoverpointBinModel *>				m_bins;
	uint32_t										m_n_bins;
	uint32_t										*m_bin_data;
	int32_t											m_hit_bin;
	std::set<uint32_t>								m_unhit_bins;
	std::set<uint32_t>								m_unreachable_bins;

};

} /* namespace ccrt */

