/*
 * CoverpointCompoundBinModel.cpp
 *
 *  Created on: Apr 21, 2019
 *      Author: ballance
 */

#include "ccrt/model/CoverpointCompoundBinModel.h"

namespace ccrt {

CoverpointCompoundBinModel::CoverpointCompoundBinModel(
		const std::string			&name,
		CoverpointModel				*parent) : CoverpointBinModelBase(name, parent) {
	// TODO Auto-generated constructor stub

}

CoverpointCompoundBinModel::CoverpointCompoundBinModel(
		const std::string							&name,
		CoverpointModel								*parent,
		const std::vector<ICoverpointBinModel *>	&bins) :
				CoverpointBinModelBase(name, parent), m_bins(bins) {
	// TODO Auto-generated constructor stub

}

CoverpointCompoundBinModel::~CoverpointCompoundBinModel() {
	// TODO Auto-generated destructor stub
}

} /* namespace ccrt */
