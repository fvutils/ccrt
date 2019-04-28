/*
 * TestRandomness.h
 *
 *  Created on: Mar 31, 2019
 *      Author: ballance
 */
#pragma once
#include "gtest/gtest.h"
#include "ccrt/ccrt.h"

using namespace ccrt;

class TestRandomness : public ::testing::Test {
public:
	TestRandomness();
	virtual ~TestRandomness();
};

