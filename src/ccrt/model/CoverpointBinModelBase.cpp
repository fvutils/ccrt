/*
 * CoverpointBinModelBase.cpp
 *
 *  Created on: Apr 21, 2019
 *      Author: ballance
 */

#include "ccrt/model/CoverpointBinModelBase.h"

namespace ccrt {

CoverpointBinModelBase::CoverpointBinModelBase(
		const std::string	&name,
		CoverpointModel		*parent) : m_name(name), m_parent(parent) {

}

CoverpointBinModelBase::~CoverpointBinModelBase() {
	// TODO Auto-generated destructor stub
}

} /* namespace ccrt */
