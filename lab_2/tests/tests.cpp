#include <gtest/gtest.h>
#include "../src/seven.h"

size_t get_size(const unsigned char * const val){
    auto i{0};
    while (val[i] != '\0'){
        i++;
    }
    return i;
}

bool validate_value(const std::string& expectedResult, const unsigned char * const result) {
    auto resultSize = get_size(result);

    if (expectedResult.length() != resultSize) return false;

    for (size_t i = 0; i < resultSize; ++i) {
        if (expectedResult[i] != result[i]) return false;
    }

    return true;
}

TEST(should_create_instance_when_number_is_valid_seven_value, string_tests) {
    const auto str = "101210";
    const auto seven = new ::seven::Seven{str};
    ASSERT_TRUE(validate_value(str, seven->get_value()));
}

TEST(should_throw_exception_when_number_is_not_valid_seven_value, string_tests) {
    EXPECT_THROW([]{
        auto seven = new ::seven::Seven{"1010108"};
        std::cout << seven->get_value();
    }(), std::out_of_range);
}

TEST(should_create_instance_when_number_is_valid_seven_value, list_tests) {
  const auto str = "123210";
  const auto seven = new ::seven::Seven{'1', '2', '3', '2', '1', '0'};
  ASSERT_TRUE(validate_value(str, seven->get_value()));
}

TEST(should_throw_exception_when_number_is_not_valid_seven_value, list_tests) {
    EXPECT_THROW(([]{
     auto seven = new ::seven::Seven{'1', '0', '3', '8', '3', '2'};
    }()), std::out_of_range);
}

TEST(should_sum_two_numbers_correctly_1, sum_tests){
    const auto h1 = ::seven::Seven("3");
    const auto h2 = ::seven::Seven("4");
    ASSERT_TRUE(validate_value("10", (h2 + h1).get_value()));
}

TEST(should_sum_two_numbers_correctly_2, sum_tests){
    const auto h1 = ::seven::Seven("15");
    const auto h2 = ::seven::Seven("2");
    ASSERT_TRUE(validate_value("20", (h2 + h1).get_value()));
}

TEST(should_sum_two_numbers_correctly_3, sum_tests){
    const auto h1 = ::seven::Seven("23");
    const auto h2 = ::seven::Seven("32");
    ASSERT_TRUE(validate_value("55", (h2 + h1).get_value()));
}

TEST(should_sum_two_numbers_correctly_if_one_is_zero_1, sum_tests){
    const auto h1 = ::seven::Seven("12345");
    const auto h2 = ::seven::Seven();
    ASSERT_TRUE(validate_value("12345", (h2 + h1).get_value()));
}

TEST(should_sum_two_numbers_correctly_if_one_is_zero_2, sum_tests){
    const auto h1 = ::seven::Seven();
    const auto h2 = ::seven::Seven("12345");
    ASSERT_TRUE(validate_value("12345", (h2 + h1).get_value()));
}

TEST(should_return_true_if_values_are_equal, eq_tests){
    const auto h1 = ::seven::Seven("12345");
    const auto h2 = ::seven::Seven("12345");
    ASSERT_TRUE(h2 == h1);
}

TEST(should_return_false_if_values_are_not_equal, eq_tests){
    const auto h1 = ::seven::Seven("12345");
    const auto h2 = ::seven::Seven("12346");
    ASSERT_FALSE(h2 == h1);
}

TEST(should_return_false_if_only_one_of_the_values_is_zero_1, eq_tests){
    const auto h1 = ::seven::Seven();
    const auto h2 = ::seven::Seven("12346");
    ASSERT_FALSE(h2 == h1);
}

TEST(should_return_false_if_only_one_of_the_values_is_zero_2, eq_tests){
    const auto h2 = ::seven::Seven();
    const auto h1 = ::seven::Seven("12346");
    ASSERT_FALSE(h2 == h1);
}

TEST(should_return_true_if_both_values_are_zero, eq_tests){
    const auto h1 = ::seven::Seven();
    const auto h2 = ::seven::Seven();
    ASSERT_TRUE(h2 == h1);
}

TEST(should_return_true_value_is_less, less_tests){
    const auto h1 = ::seven::Seven("12345");
    const auto h2 = ::seven::Seven("12346");
    ASSERT_TRUE(h1 < h2);
}

TEST(should_return_false_value_is_not_less, less_tests){
    const auto h1 = ::seven::Seven("12345");
    const auto h2 = ::seven::Seven();
    ASSERT_FALSE(h1 < h2);
}

TEST(should_return_true_value_is_greater, greater_tests){
    const auto h1 = ::seven::Seven("12346");
    const auto h2 = ::seven::Seven("12345");
    ASSERT_TRUE(h1 > h2);
}

TEST(should_return_false_value_is_not_greater, greater_tests){
    const auto h1 = ::seven::Seven();
    const auto h2 = ::seven::Seven("12345");
    ASSERT_FALSE(h1 > h2);
}

TEST(should_throw_exception_when_result_is_negative, subtraction_tests){
    EXPECT_THROW(
        []{
          const auto h1 = ::seven::Seven("3");
          const auto h2 = ::seven::Seven("4");
          const auto h3 = h1 - h2;
        }(), std::invalid_argument
    );
}

TEST(should_subtract_two_numbers_correctly_1, subtraction_tests){
    const auto h1 = ::seven::Seven("4");
    const auto h2 = ::seven::Seven("3");
    ASSERT_TRUE(validate_value("1", (h1 - h2).get_value()));
}

TEST(should_subtract_two_numbers_correctly_2, subtraction_tests){
    const auto h1 = ::seven::Seven("32");
    const auto h2 = ::seven::Seven("23");
    const auto result = h1 - h2;
    ASSERT_TRUE(validate_value("6", result.get_value()));
}

TEST(should_substract_two_numbers_correctly_3, subtraction_tests){
    const auto h1 = ::seven::Seven("66");
    const auto h2 = ::seven::Seven();
    ASSERT_TRUE(validate_value("66", (h1 - h2).get_value()));
}

TEST(should_subtract_two_numbers_correctly, isubtraction_tests){
    auto h1 = ::seven::Seven("32");
    const auto h2 = ::seven::Seven("23");
    h1 -= h2;
    ASSERT_TRUE(validate_value("6", h1.get_value()));
}

TEST(should_sum_two_numbers_correctly, isum_tests){
    auto h1 = ::seven::Seven("23");
    const auto h2 = ::seven::Seven("32");
    h1 += h2;
    ASSERT_TRUE(validate_value("55", h1.get_value()));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
