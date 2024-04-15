#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../Replace/Replace/Replace.h"
#include "../../catch2/catch.hpp"

TEST_CASE("Replacing an empty string")
{
	std::string inputString = "шла саша по шоссе и сосала сушку";
	std::string searchString = "";
	std::string replacementString = "нет";
	std::string expected = "шла саша по шоссе и сосала сушку";
	std::string result = ReplaceString(inputString, searchString, replacementString);
	REQUIRE(result == expected);
}

TEST_CASE("Replace with an empty string")
{
	std::string inputString = "смотрим на последнее слово";
	std::string searchString = "слово";
	std::string replacementString = "";
	std::string expected = "смотрим на последнее ";
	std::string result = ReplaceString(inputString, searchString, replacementString);
	REQUIRE(result == expected);
}

TEST_CASE("String replacement with possible looping")
{
	std::string inputString = "мила мыла руки мылом";
	std::string searchString = "мы";
	std::string replacementString = "мыло";
	std::string expected = "мила мылола руки мылолом";
	std::string result = ReplaceString(inputString, searchString, replacementString);
	REQUIRE(result == expected);
}

TEST_CASE("String replacement with part repetition")
{
	std::string inputString = "123111115";
	std::string searchString = "11111";
	std::string replacementString = "4";
	std::string expected = "12345";
	std::string result = ReplaceString(inputString, searchString, replacementString);
	REQUIRE(result == expected);
}

TEST_CASE("Given invalid files")
{
	SECTION("Input file doesn't exist")
	{
		REQUIRE_THROWS_AS(CopyFileWithReplacement("test-data/dog.txt", "test-data/fox.txt", "cat", "dog"), std::invalid_argument);
	}

	SECTION("Output file doesn't exist")
	{
		REQUIRE_THROWS_AS(CopyFileWithReplacement("test-data/fox-replace-dog-with-cat.txt", "test-data/dog.txt", "cat", "dog"), std::invalid_argument);
	}
}