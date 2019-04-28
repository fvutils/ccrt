/*
 * Cross.h
 *
 *  Created on: Apr 26, 2019
 *      Author: ballance
 */
#pragma once
#include <string>
#include <functional>
#include <initializer_list>

namespace ccrt {

class Coverpoint;
class CoverpointCrossModel;

class Cross {
public:
	Cross(
		const std::string					&name,
		std::initializer_list<Coverpoint>	cp_list);

	virtual ~Cross();

private:
	CoverpointCrossModel					*m_model;

};

} /* namespace ccrt */

