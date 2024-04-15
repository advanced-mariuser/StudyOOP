#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <Windows.h>
#include <../../Dictionary.h>

using namespace std;

struct Args
{
	string dictionaryFileName;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw invalid_argument("Invalid argument count\nUsage: dictionary.exe <dictionary_file>\n");
	}

	Args args;
	args.dictionaryFileName = argv[1];

	return args;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try
	{
		Args args = ParseArgs(argc, argv);
		string dictionary_filename = args.dictionaryFileName;

		map<string, vector<string>> dictionary;

		LoadDictionary(dictionary_filename, dictionary);
		RunDictionaryProgram(dictionary);
		SaveChanges(dictionary_filename, dictionary);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}