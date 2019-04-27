/*
 * CoverpointCompoundBinModel.h
 *
 *  Created on: Apr 21, 2019
 *      Author: ballance
 */
#pragma once
#include <vector>

#include "model/CoverpointBinModelBase.h"

namespace ccrt {

class CoverpointCompoundBinModel : public CoverpointBinModelBase {
public:
	CoverpointCompoundBinModel(
			const std::string			&name,
			CoverpointModel				*parent);

	CoverpointCompoundBinModel(
			const std::string							&name,
			CoverpointModel								*parent,
			const std::vector<ICoverpointBinModel *>	&bins);

	virtual ~CoverpointCompoundBinModel();

	void add_bin(ICoverpointBinModel *bin);

private:
	std::vector<ICoverpointBinModel *>		m_bins;
};

} /* namespace ccrt */

