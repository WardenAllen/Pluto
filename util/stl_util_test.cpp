
#include <gtest/gtest.h>

#include "stl_util.h"

using namespace std;
using namespace pluto::util;

TEST(PLUTO, STL_LOOP_DELETE) {
	unordered_map<int, int> hash;
	for (int i = 0; i < 100; i++)
		hash[i] = i;

	int a = 1;

	STL_LOOP_DELETE(hash, ([&a](const auto& item) {
		auto const& [key, value] = item;
		a = 2;
		return (key & 1) == 1;
	}));

	EXPECT_EQ(hash.size(), 50);

	vector<int> vec;
	for (int i = 0; i < 100; i++)
		vec.push_back(i);

	STL_LOOP_DELETE(vec, ([&a](const auto& item) {
		return (item & 1) == 1;
	}));

	EXPECT_EQ(vec.size(), 50);
}

TEST(PLUTO, STL_CLEAR) {
	vector<int*> vec;
	vec.push_back(new int);
	stl_clear(vec);
	EXPECT_EQ(vec.size(), 0);

	map<int, int*> mm;
	mm.emplace(1, new int);
	stl_clear(mm);
	EXPECT_EQ(mm.size(), 0);
}

TEST(PLUTO, TYPE_TRAIT_FUNC_OVERLOAD) {
	EXPECT_NE(&(test<int>), &(test<map<int, int>>));
}