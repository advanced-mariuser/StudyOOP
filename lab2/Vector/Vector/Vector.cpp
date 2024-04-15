#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

vector<double> ParseDoublesToVector(istream& input)
{
	vector<double> vector(istream_iterator<double>(input), (istream_iterator<double>()));

	return vector;
};

void AddAverageOfPositives(vector<double>& vector)
{
	size_t count;
	double sum = accumulate(vector.begin(), vector.end(), 0.0,
		[&](double acc, double val) {
			count = val > 0 ? count++ : count;
			return val > 0 ? acc + val : acc;
		});

	if (sum == 0.0)
	{
		return;
	}

	double average = sum / count;

	transform(vector.begin(), vector.end(), vector.begin(), [average](int& elem) {
		return elem + average;
	});
}