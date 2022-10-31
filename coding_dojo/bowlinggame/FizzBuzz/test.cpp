#include <vector>
#include <gmock/gmock.h>
#include "FizzBuzz.hpp"

class FizzBuzzTest: public ::testing::Test
{
public:
    FizzBuzz fizzbuzz;
private:
};

TEST(fizzbuzz_test, test_one)
{
    FizzBuzz fizzbuzz;

	ASSERT_EQ("1", fizzbuzz.output(1));
}

TEST_F(FizzBuzzTest, test_3)
{
	ASSERT_EQ("Fizz", fizzbuzz.output(3));
}

TEST_F(FizzBuzzTest, test_5)
{
	ASSERT_EQ("Buzz", fizzbuzz.output(5));
}

TEST_F(FizzBuzzTest, test_15)
{
	ASSERT_EQ("FizzBuzz", fizzbuzz.output(15));
}

TEST_F(FizzBuzzTest, test_7)
{
	ASSERT_EQ("Whizz", fizzbuzz.output(7));
}

TEST_F(FizzBuzzTest, test_21)
{
	ASSERT_EQ("FizzWhizz", fizzbuzz.output(21));
}