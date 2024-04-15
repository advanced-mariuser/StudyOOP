#include <set>
#include <vector>
#include <cassert>

using namespace std;

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	/*
	������� �������� � O(logN)
	����� �������� � O(logN)
	�������� �������� � O(logN)
	������� ��������� � O(1)
	*/
	
	if (upperBound < 2)
	{
		return {};
	}

	vector<bool> isPrime((upperBound + 1)/2, true);
	set<int> primesSet;

	auto isOddPrime = [&isPrime](int oddNumber) -> vector<bool>::reference {
		assert(oddNumber % 2 == 1);
		return isPrime[oddNumber / 2];
	};

	int number = 3;
	while (number * number <= upperBound)
	{
		if (isOddPrime(number))
		{
			for (int i = number * number; i <= upperBound; i += 2 * number)
			{
				isOddPrime(i) = false;
			}
		}
		number += 2;
	}

	primesSet.insert(2);
	for (int i = 1; i < isPrime.size(); ++i)
	{
		if (isPrime[i])
		{
			// ��������� ��� ��������� ������ ���� ��������
			/* ������ - ������ ������� */ 			
			primesSet.insert(primesSet.end(), 2 * i + 1);
		}
	}

	return primesSet;
}