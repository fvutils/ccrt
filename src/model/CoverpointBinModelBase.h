/*
 * CoverpointBinModelBase.h
 *
 *  Created on: Apr 21, 2019
 *      Author: ballance
 */
#pragma once
#include <string>

#include "ICoverpointBinModel.h"

namespace ccrt {

class CoverpointModel;

class CoverpointBinModelBase : public virtual ICoverpointBinModel {
public:
	CoverpointBinModelBase(
			const std::string		&name,
			CoverpointModel			*parent);

	virtual ~CoverpointBinModelBase();

protected:
	std::string						m_name;
	CoverpointModel					*m_parent;
};

} /* namespace ccrt */

