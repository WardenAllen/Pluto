
#include <gtest/gtest.h>

#include "type_traits_util.h"

using namespace std;
using namespace pluto::util;

TEST(PLUTO, TYPE_TRAITS_IS_STRING) {

	EXPECT_EQ(is_string<string>::value, true);
	EXPECT_EQ(is_string<string&>::value, true);
	EXPECT_EQ(is_string<string*>::value, false);
	EXPECT_EQ(is_string<const string&>::value, true);
	EXPECT_EQ(is_string<const volatile string&>::value, true);

	EXPECT_EQ(is_string<wstring>::value, true);
	EXPECT_EQ(is_string<wstring&>::value, true);
	EXPECT_EQ(is_string<wstring*>::value, false);
	EXPECT_EQ(is_string<const wstring&>::value, true);
	EXPECT_EQ(is_string<const volatile wstring&>::value, true);

	EXPECT_EQ(is_string<int>::value, false);
}

TEST(PLUTO, TYPE_TRAITS_PARSE_STRING) {

	string s = "111";

	EXPECT_TRUE(parse_string(s) == s);
	EXPECT_TRUE(parse_string(111) == s);
	EXPECT_TRUE(parse_string("111") == s);

}
