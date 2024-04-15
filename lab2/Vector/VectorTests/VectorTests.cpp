#include <sstream>
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../Vector/Vector.h"
#include "../../../lab1/catch2/catch.hpp"

using namespace std;

TEST_CASE("Empty input stream yields empty vector")
{
	istringstream input("");
	vector<double> result = ParseDoublesToVector(input);

	REQUIRE(result.empty());
}

TEST_CASE("Parsing valid input stream to vector of doubles")
{
	std::istringstream input("1.5 2.7 3.9");
	std::vector<double> result = ParseDoublesToVector(input);

	REQUIRE(result[0] == Approx(1.5));
	REQUIRE(result[1] == Approx(2.7));
	REQUIRE(result[2] == Approx(3.9));
}

TEST_CASE("Adding average of positives to vector")
{
	vector<double> vec = { 1.0, 2.0, -3.0, 4.0, -5.0 };
	AddAverageOfPositives(vec);
	vector<double> expected = { 3.3333333333, 4.3333333333, -0.6666666667, 6.3333333333, -2.6666666667 };

	for (size_t i = 0; i < expected.size(); ++i)
	{
		REQUIRE(vec[i] == Approx(expected[i]));
	}
}

TEST_CASE("Empty vector remains unchanged")
{
	vector<double> vec;
	AddAverageOfPositives(vec);

	REQUIRE(vec.empty());
}

TEST_CASE("Vector with only negative values remains unchanged")
{
	vector<double> vec = { -1.0, -2.0, -3.0 };
	AddAverageOfPositives(vec);
	vector<double> expected = { -1.0, -2.0, -3.0 };

	REQUIRE(vec == expected);
}
