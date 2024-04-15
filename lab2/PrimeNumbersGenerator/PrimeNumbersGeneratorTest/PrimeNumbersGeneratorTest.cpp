#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../lab1/catch2/catch.hpp"
#include "../PrimeNumbersGenerator/PrimeNumbersGenerator.h"

using namespace std;

TEST_CASE("Generate prime numbers set")
{
	SECTION("Upper bound is 0")
	{
		set<int> primes = GeneratePrimeNumbersSet(0);
		set<int> expected = {};
		REQUIRE(primes == expected);
	}

	SECTION("Upper bound is 1")
	{
		set<int> primes = GeneratePrimeNumbersSet(1);
		set<int> expected = {};
		REQUIRE(primes == expected);
	}

	SECTION("Upper bound is 2")
	{
		set<int> primes = GeneratePrimeNumbersSet(2);
		set<int> expected = { 2 };
		REQUIRE(primes == expected);
	}

	SECTION("Upper bound is 9")
	{
		set<int> primes = GeneratePrimeNumbersSet(9);
		set<int> expected = { 2, 3, 5, 7 };
		REQUIRE(primes == expected);
	}

	SECTION("Upper bound is 10")
	{
		set<int> primes = GeneratePrimeNumbersSet(10);
		set<int> expected = { 2, 3, 5, 7 };
		REQUIRE(primes == expected);
	}

	SECTION("Upper bound is 20")
	{
		set<int> primes = GeneratePrimeNumbersSet(20);
		set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19 };
		REQUIRE(primes == expected);
	}

	SECTION("Upper bound is 100000000")
	{
		set<int> primes = GeneratePrimeNumbersSet(100000000);
		REQUIRE(primes.size() == 5761455);
	}
}
