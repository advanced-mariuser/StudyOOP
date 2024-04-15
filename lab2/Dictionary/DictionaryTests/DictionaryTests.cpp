#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../lab1/catch2/catch.hpp"
#include "../../Dictionary/Dictionary/Dictionary.h"

TEST_CASE("LoadDictionary Function Test")
{
	Dictionary dictionary;
	SECTION("Valid File")
	{
		REQUIRE_NOTHROW(LoadDictionary("../test-data/dictionary.txt", dictionary));
		REQUIRE(dictionary["cat"] == "кошка");
		REQUIRE(dictionary["dog"] == "собака");
		REQUIRE(dictionary["fish"] == "рыба");
	}

	SECTION("Invalid File")
	{
		REQUIRE_THROWS_AS(LoadDictionary("nonexistent_file.txt", dictionary), invalid_argument);
	}
}

TEST_CASE("SaveDictionary Function Test")
{
	Dictionary dictionary = { { "dog", "собака" }, { "cat", "кошка" }, { "fish", "рыба" } };
	SECTION("Valid File")
	{
		REQUIRE_NOTHROW(SaveDictionary("../test-data/dictionary.txt", dictionary));
	}

	SECTION("Invalid File")
	{
		REQUIRE_THROWS_AS(SaveDictionary("/invalid/path/test_output.txt", dictionary), invalid_argument);
	}
}
