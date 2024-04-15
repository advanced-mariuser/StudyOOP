#include "Invert.h"
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

template <size_t N>
using SquareMatrix = array<array<double, N>, N>;

double roundToThreeDecimals(double value)
{
	return round(value * 1000.0) / 1000.0;
}

void Print3x3Matrix(const SquareMatrix<MATRIX_DIMENTION>& inputMatrix)
{
	for (const auto& row : inputMatrix)
	{
		for (const auto& item : row)
		{
			cout << item << " ";
		}
		cout << endl;
	}
}

SquareMatrix<3> Read3x3MatrixFromFile(const string& inputFileName)
{
	ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
		throw invalid_argument("Failed to open input file");

	SquareMatrix<MATRIX_DIMENTION> matrix;
	string line;

	for (size_t i = 0; i < MATRIX_DIMENTION; ++i)
	{
		if (!getline(inputFile, line))
		{
			throw runtime_error("Failed to read matrix row from input file");
		}

		istringstream iss(line);
		for (size_t j = 0; j < MATRIX_DIMENTION; ++j)
		{
			if (!(iss >> matrix[i][j]))
			{
				throw runtime_error("Failed to parse matrix element from input file");
			}
		}
	}

	return matrix;
}

template <size_t N>
double Determinant(const SquareMatrix<N>& matrix)
{
	//сложно (не усложнять)
	double det = 0.0;

	if constexpr (N == 1)
	{
		det = matrix[0][0];
	}
	else if constexpr (N == 2)
	{
		det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else
	{
		for (size_t j = 0; j < N; ++j)
		{
			SquareMatrix<N - 1> minor;
			size_t minorRow = 0;
			for (size_t k = 1; k < N; ++k)
			{
				size_t minorCol = 0;
				for (size_t l = 0; l < N; ++l)
				{
					if (l == j)
						continue;
					minor[minorRow][minorCol] = matrix[k][l];
					++minorCol;
				}
				++minorRow;
			}
			double minorDet = Determinant<N - 1>(minor);
			det += (j % 2 == 0 ? 1 : -1) * matrix[0][j] * minorDet;
		}
	}

	return det;
}

SquareMatrix<MATRIX_DIMENTION> Transpose3x3Matrix(const SquareMatrix<MATRIX_DIMENTION>& matrix)
{
	SquareMatrix<MATRIX_DIMENTION> result;

	for (size_t i = 0; i < MATRIX_DIMENTION; ++i)
	{
		for (size_t j = 0; j < MATRIX_DIMENTION; ++j)
		{
			result[j][i] = matrix[i][j];
		}
	}

	return result;
}

SquareMatrix<MATRIX_DIMENTION> Cofactor3x3Matrix(const SquareMatrix<MATRIX_DIMENTION>& matrix)
{
	//сложно ничего не понятно
	SquareMatrix<MATRIX_DIMENTION> cofactor;

	for (size_t i = 0; i < MATRIX_DIMENTION; ++i)
	{
		for (size_t j = 0; j < MATRIX_DIMENTION; ++j)
		{
			SquareMatrix<MINOR_MATRIX_DIMENTION> minor;
			size_t minorRow = 0;
			for (size_t k = 0; k < MATRIX_DIMENTION; ++k)
			{
				if (k == i)
					continue;
				size_t minorCol = 0;
				for (size_t p = 0; p < MATRIX_DIMENTION; ++p)
				{
					if (p == j)
						continue;
					minor[minorRow][minorCol] = matrix[k][p];
					++minorCol;
				}
				++minorRow;
			}
			
			double minorDet = Determinant<MINOR_MATRIX_DIMENTION>(minor);
			cofactor[i][j] = (i + j) % MINOR_MATRIX_DIMENTION == 0 ? minorDet : -minorDet;
		}
	}

	return cofactor;
}

SquareMatrix<MATRIX_DIMENTION> Invert3x3Matrix(const SquareMatrix<MATRIX_DIMENTION>& matrix)
{
	double det = Determinant<MATRIX_DIMENTION>(matrix);
	if (det == 0)
	{
		throw std::invalid_argument("Matrix is singular, inverse does not exist");
	}

	SquareMatrix<MATRIX_DIMENTION> cofactorMatrix = Cofactor3x3Matrix(matrix);
	SquareMatrix<MATRIX_DIMENTION> transporantMatrix = Transpose3x3Matrix(cofactorMatrix);

	SquareMatrix<MATRIX_DIMENTION> inverse;

	//вынести в функцию и испольщовать можно range based for
	for (size_t i = 0; i < MATRIX_DIMENTION; ++i)
	{
		for (size_t j = 0; j < MATRIX_DIMENTION; ++j)
		{
			//округлять при выводе
			//прочитать про манимуляторы вывода и использовать их чтобы выводить 
			inverse[i][j] = roundToThreeDecimals(transporantMatrix[i][j] / det);
		}
	}

	return inverse;
}

void InvertMatrixFromFile(const string& inputFileName)
{
	SquareMatrix<MATRIX_DIMENTION> matrix = Read3x3MatrixFromFile(inputFileName);

	SquareMatrix<MATRIX_DIMENTION> invertedMatrix = Invert3x3Matrix(matrix);

	Print3x3Matrix(invertedMatrix);
}