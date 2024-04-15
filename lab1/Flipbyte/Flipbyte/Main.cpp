#include <iostream>
#include <string>
#include <cstdint>
#include "FlipByte.h"

struct Args
{
	uint8_t inputByte;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid argument count\nUsage: flipbyte.exe <inputByte>\n");
	}
	
	if (std::stoi(argv[1]) <= 0 || std::stoi(argv[1]) >= UINT8_MAX)
	{
		throw std::out_of_range("Argument inputByte is out of range\n");
	}

	Args args;
	args.inputByte = std::stoi(argv[1], nullptr, 16);

	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
	
		uint8_t outputByte = BinaryBitOrderingChange(args.inputByte);

		PrintNumber(outputByte);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}