#include <iostream>
#include <cstdint>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../../Flipbyte/Flipbyte/FlipByte.h"

TEST_CASE("Flipping with correct input")
{
	SECTION("Input is small byte value")
	{
		int inputByte = 1;
		uint8_t result = BinaryBitOrderingChange(inputByte);
		uint8_t expected = 128;
		REQUIRE(result == expected);
	}

	SECTION("Input is average byte value")
	{
		int inputByte = 128;
		uint8_t result = BinaryBitOrderingChange(inputByte);
		uint8_t expected = 1;
		REQUIRE(result == expected);
	}

	SECTION("Input is big byte value")
	{
		int inputByte = 254;
		uint8_t result = BinaryBitOrderingChange(inputByte);
		uint8_t expected = 127;
		REQUIRE(result == expected);
	}
}

TEST_CASE("Print with correct input")
{
	uint8_t inputByte = 128;
	REQUIRE_NOTHROW(PrintNumber(inputByte));
}

TEST_CASE("Print number with NULL")
{
	REQUIRE_THROWS_AS(PrintNumber(NULL), std::invalid_argument);
}
