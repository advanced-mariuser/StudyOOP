#include "Replace.h"
#include <iostream>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string search;
	std::string replace;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument("Invalid argument count\nUsage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n");
	}
	
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	args.search = argv[3];
	args.replace = argv[4];

	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		CopyFileWithReplacement(args.inputFileName, args.outputFileName, args.search, args.replace);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}