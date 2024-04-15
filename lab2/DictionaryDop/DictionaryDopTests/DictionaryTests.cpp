#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../lab1/catch2/catch.hpp"
#include "../../Dictionary/Dictionary/Dictionary.h"

TEST_CASE("Input correct html string")
{
	std::string input = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string result = HtmlDecode(input);
	std::string expected = "Cat <says> \"Meow\". M&M's";
	REQUIRE(result == expected);
}

TEST_CASE("Input string without html code")
{
	std::string input = "Cat says Meow. M&M's";
	std::string result = HtmlDecode(input);
	std::string expected = "Cat says Meow. M&M's";
	REQUIRE(result == expected);
}

TEST_CASE("Input empty string")
{
	std::string input = "";
	std::string result = HtmlDecode(input);
	std::string expected = "";
	REQUIRE(result == expected);
}

TEST_CASE("Input html string with the typo")
{
	SECTION("Typo in &lt;")
	{
		std::string input = "Cat &ltsays&gt; &quot;Meow&quot;. M&&amp;M&apos;s";
		std::string result = HtmlDecode(input);
		std::string expected = "Cat &ltsays> \"Meow\". M&&M's";
		REQUIRE(result == expected);
	}
	SECTION("Typo in &quot")
	{
		std::string input = "This is a &qot;test&gt; with &amp;typops; entities.";
		std::string result = HtmlDecode(input);
		std::string expected = "This is a &qot;test> with &typops; entities.";
		REQUIRE(result == expected);
	}
	SECTION("Typo in &gt;")
	{
		std::string input = "&lt;p&gt;Hello&lt;/p&gd;";
		std::string result = HtmlDecode(input);
		std::string expected = "<p>Hello</p&gd;";
		REQUIRE(result == expected);
	}
}