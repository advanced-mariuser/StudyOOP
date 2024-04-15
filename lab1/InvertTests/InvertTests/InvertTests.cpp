#include <fstream>
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../Invert/Invert/Invert.h"
#include "../../catch2/catch.hpp"

TEST_CASE("Invert with correct input")
{
	SECTION("Matrix with int value")
	{
		SquareMatrix<3> inputMatrix = { { { 2, -1, 3 },
			{ 0, 1, 4 },
			{ -3, 2, -1 } } };
		double det = Determinant<3>(inputMatrix);
		SquareMatrix<3> result = Invert3x3Matrix(inputMatrix);
		SquareMatrix<3> expected = { { { -3.0, 1.667, -2.333 },
			{ -4.0, 2.333, -2.667 },
			{ 1.0, -0.333, 0.667 } } };
		REQUIRE(result == expected);
	}

	SECTION("Matrix with double valuee")
	{
		SquareMatrix<3> inputMatrix = { { { -0.5, 0.2, 0.1 },
			{ 0.3, -0.7, 0.4 },
			{ 0.6, 0.8, -0.9 } } };
		SquareMatrix<3> result = Invert3x3Matrix(inputMatrix);
		SquareMatrix<3> expected = { { { 23.846, 20, 11.538 },
			{ 39.231, 30, 17.692 },
			{ 50.769, 40, 22.308 } } };
		REQUIRE(result == expected);
	}
}

TEST_CASE("Data in file isn't correct")
{
	SECTION("Given 3x3 Matrix but with invalid value")
	{
		std::ofstream tempFile("temp_matrix.txt");
		if (!tempFile.is_open())
		{
			FAIL("Failed to create temporary file");
		}

		tempFile << "2  =1  3" << std::endl;
		tempFile << "0   1  4.0" << std::endl;
		tempFile << "-3  2   -1" << std::endl;
		tempFile.close();

		std::string inputFileName = "temp_matrix.txt";

		REQUIRE_THROWS_AS(InvertMatrixFromFile(inputFileName), std::runtime_error);
	}
	
	SECTION("Given 2x2 Matrix")
	{
		std::ofstream tempFile("temp_matrix.txt");
		if (!tempFile.is_open())
		{
			FAIL("Failed to create temporary file");
		}

		tempFile << "2  =1" << std::endl;
		tempFile << "0   1" << std::endl;
		tempFile.close();

		std::string inputFileName = "temp_matrix.txt";

		REQUIRE_THROWS_AS(InvertMatrixFromFile(inputFileName), std::runtime_error);
	}

	SECTION("Given 3x3 Matrix but is singular")
	{
		std::ofstream tempFile("temp_matrix.txt");
		if (!tempFile.is_open())
		{
			FAIL("Failed to create temporary file");
		}

		tempFile << "1   4  2" << std::endl;
		tempFile << "0   0  0" << std::endl;
		tempFile << "3   9  5" << std::endl;
		tempFile.close();

		std::string inputFileName = "temp_matrix.txt";

		REQUIRE_THROWS_AS(InvertMatrixFromFile(inputFileName), std::invalid_argument);
	}
}

TEST_CASE("Given invalid file")
{
	REQUIRE_THROWS_AS(InvertMatrixFromFile("test-data/mat.txt"), std::invalid_argument);
}
