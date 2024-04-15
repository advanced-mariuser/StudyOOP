#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../Replace/Replace/Replace.h"
#include "../../catch2/catch.hpp"

TEST_CASE("Replacing an empty string")
{
	std::string inputString = "��� ���� �� ����� � ������ �����";
	std::string searchString = "";
	std::string replacementString = "���";
	std::string expected = "��� ���� �� ����� � ������ �����";
	std::string result = ReplaceString(inputString, searchString, replacementString);
	REQUIRE(result == expected);
}

TEST_CASE("Replace with an empty string")
{
	std::string inputString = "������� �� ��������� �����";
	std::string searchString = "�����";
	std::string replacementString = "";
	std::string expected = "������� �� ��������� ";
	std::string result = ReplaceString(inputString, searchString, replacementString);
	REQUIRE(result == expected);
}

TEST_CASE("String replacement with possible looping")
{
	std::string inputString = "���� ���� ���� �����";
	std::string searchString = "��";
	std::string replacementString = "����";
	std::string expected = "���� ������ ���� �������";
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