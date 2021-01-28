
#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>

#include <gtest/gtest.h>

#include "time_util.h"
#include "stl_util.h"

using namespace std;
using namespace pluto;

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}