#pragma once
#include <fstream>
#include <vector>

std::vector<double> ParseDoublesToVector(std::istream& input);
void AddAverageOfPositives(std::vector<double>& vector);