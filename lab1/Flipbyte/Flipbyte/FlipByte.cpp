#include "FlipByte.h"
#include <iostream>
#include <cstdint>
#include <functional>

void PrintNumber(uint8_t number)
{
    if (number == NULL)
    {
		throw std::invalid_argument("No input arguments");
    }
	std::cout << static_cast<int>(number) << std::endl;
}

uint8_t GetBits(uint8_t x, int p, int n)
{
	return (x >> (p + 1 - n)) & ~(~0 << n);
} 


void MergeSortBits(uint8_t byte, int l, int r)
{
	if (l >= r)
	{
		return;
	}

	int mid = (l + r) / 2;

	MergeSortBits(byte, l, mid);
	MergeSortBits(byte, mid + 1, r);


}

uint8_t BinaryBitOrderingChange(uint8_t inputByte)
{
	return MergeSortBits(inputByte, 0, 7);
}