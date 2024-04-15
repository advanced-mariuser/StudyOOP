#include <../../Vector.h>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Вариант 1:
// Прибавить к каждому элементу массива среднее арифметическое его положительных элементов
// Подсказка: используйте алгоритм std::accumulate, чтобы найти сумму положительных элементов.

int main()
{
	cout << "Enter array of double" << endl;

	vector<double> inputData;

	inputData = ParseDoublesToVector(cin);

	AddAverageOfPositives(inputData);

	std::cout << std::setprecision(2) << std::fixed;

	std::sort(begin(inputData), end(inputData));

	for (const auto& elem : inputData)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	return EXIT_SUCCESS;
}