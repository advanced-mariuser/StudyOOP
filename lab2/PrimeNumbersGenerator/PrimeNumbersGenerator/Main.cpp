#include <../../PrimeNumbersGenerator.h>
#include <iostream>
#include <string>

using namespace std;

struct Args
{
	int upperBound;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw invalid_argument("Invalid argument count\nUsage: invert.exe <upperBound>\n");
	}

	Args args;
	args.upperBound = stoi(argv[1]);

	if (args.upperBound <= 0 || args.upperBound > 100000000)
	{
		throw range_error("Upper bound should be a positive integer not exceeding 100 million.");
	}

	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		set<int> primes = GeneratePrimeNumbersSet(args.upperBound);

		for (int prime : primes)
		{
			cout << prime << " ";
		}
		cout << endl;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}