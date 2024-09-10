#include <numeric>
#include <gtest/gtest.h>
#include "../src/bin_to_int.h"

TEST(test_01, test_set)
{
    auto binary_string = "11011";
    ASSERT_EQ(from_bin_to_int(binary_string), 15);
}

TEST(test_02, test_set)
{
    auto binary_string = "1101101";
    ASSERT_EQ(from_bin_to_int(binary_string), 31);
}

TEST(test_03, test_set)
{
    auto binary_string = "0000001";
    ASSERT_EQ(from_bin_to_int(binary_string), 1);
}

TEST(test_04, test_set)
{
    auto binary_string = "000";
    ASSERT_EQ(from_bin_to_int(binary_string), 0);
}

TEST(test_05, test_set)
{
    auto binary_string = "100001";
    ASSERT_EQ(from_bin_to_int(binary_string), 3);
}

TEST(test_06, test_set)
{
    auto binary_string = "100000";
    ASSERT_EQ(from_bin_to_int(binary_string), 1);
}

TEST(test_07, test_set)
{
    auto binary_string = "010101011";
    ASSERT_EQ(from_bin_to_int(binary_string), 31);
}

TEST(test_08, test_set)
{
    auto binary_string = "0111111111110";
    ASSERT_EQ(from_bin_to_int(binary_string), 2047);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}