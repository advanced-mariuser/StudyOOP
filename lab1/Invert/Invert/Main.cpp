#include "Invert.h"
#include <iostream>
#include <string>

struct Args
{
	std::string inputFileName;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid argument count\nUsage: invert.exe <inputFileName>\n");
	}

	Args args;
	args.inputFileName = argv[1];

	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		InvertMatrixFromFile(args.inputFileName);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}