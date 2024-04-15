#pragma once
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// вы€снить почему inline
inline constexpr int MATRIX_DIMENTION = 3;
inline constexpr int MINOR_MATRIX_DIMENTION = 2;

template <size_t N>
using SquareMatrix = std::array<std::array<double, N>, N>;

using Matrix3x3 = SquareMatrix<3>;

template <size_t N>
double Determinant(const SquareMatrix<N>& matrix);

SquareMatrix<MATRIX_DIMENTION> Invert3x3Matrix(const SquareMatrix<MATRIX_DIMENTION>& matrix);

void InvertMatrixFromFile(const std::string& inputFileName);