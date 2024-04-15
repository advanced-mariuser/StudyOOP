#include <../../Vector.h>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ������� 1:
// ��������� � ������� �������� ������� ������� �������������� ��� ������������� ���������
// ���������: ����������� �������� std::accumulate, ����� ����� ����� ������������� ���������.

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