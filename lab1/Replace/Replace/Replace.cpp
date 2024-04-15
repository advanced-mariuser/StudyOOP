#include "Replace.h"
#include <fstream>
#include <string>
#include <iostream>

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;

	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);

		result.append(subject, pos, foundPos - pos);
		if (foundPos == std::string::npos)
		{
			break;
		}
		result.append(replacementString);

		pos = foundPos + searchString.length();
	}
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

void CopyFileWithReplacement(const std::string& inputFileName, const std::string& outputFileName,
	const std::string& searchString, const std::string& replaceString)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Failed to open input file");
	}

	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		throw std::invalid_argument("Failed to open output file");
	}

	CopyStreamWithReplacement(inputFile, outputFile, searchString, replaceString);

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to write file on disk");
	}

	std::cout << "The string was successfully replaced in the file" << std::endl;
}