#include <string>
#include <vector>
#include <map>
#include <gmock/gmock.h>
#include "FizzBuzz.hpp"

std::map<int, std::string> number_to_string_map = 
{
	{3, "Fizz"},
	{5, "Buzz"},
	{7, "Whizz"}
};

std::string FizzBuzz::output(int value)
{
	std::string result = "";

	for (auto &it : number_to_string_map)
	{
		if (value % it.first == 0)
		{
			result += it.second;
		}
	}

	if (result == "")		
		result = std::to_string(value);

	return result;		
}

int main(int argc, char** argv)
{
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
