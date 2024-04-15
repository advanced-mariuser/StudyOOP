#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

using Dictionary = map<string, string>;
//посмотреть как тестировать ввод вывод на примере программы телевизор
void LoadDictionary(const string& dictionary_filename, Dictionary& dictionary)
{
	ifstream file(dictionary_filename);
	if (!file.is_open())
	{
		throw invalid_argument("Failed to open dictionary file");
	}

	string line;
	while (getline(file, line))
	{
		//придумать способ обработки словаря чтобы можно было писать : ,
		size_t delimiter_pos = line.find(':');
		if (delimiter_pos != string::npos)
		{
			string key = line.substr(0, delimiter_pos);
			string value = line.substr(delimiter_pos + 1);

			dictionary[key] = value;
		}
	}

	file.close();
}

void SaveDictionary(const string& filename, const Dictionary& dictionary)
{
	ofstream file(filename);
	if (!file.is_open())
	{
		throw invalid_argument("Failed to open output file");
	}

	for (const auto& pair : dictionary)
	{
		file << pair.first << ":" << pair.second << endl;
	}

	if (!file.flush())
	{
		throw runtime_error("Failed to write file on disk");
	}
}

void SaveChanges(const string& dictionary_filename, const Dictionary& dictionary)
{
	string save_decision;

	while (save_decision != "y" || save_decision != "n")
	{
		cout << "Would you like to save changes to the dictionary? (y/n): ";
		getline(cin, save_decision);
		if (save_decision == "y")
		{
			SaveDictionary(dictionary_filename, dictionary);
			cout << "Changes saved." << endl;
			break;
		}
		else if (save_decision == "n")
		{
			cout << "Changes doesn't saved." << endl;
			break;
		}
	}
}
//если не было изменений то не надо предлагать сохранять
void RunDictionaryProgram(Dictionary& dictionary)
{
	string input;
	while (true)
	{
		cout << "Enter a word or phrase in English (type '...' to exit): ";
		getline(cin, input);

		if (input == "...")
		{
			cout << "Exiting..." << endl;
			break;
		}

		if (dictionary.find(input) != dictionary.end())
		{
			cout << "Translation: " << dictionary[input] << endl;
		}
		else
		{
			cout << "Translation not found. Enter translation or leave empty to skip: ";
			string translation;
			getline(cin, translation);
			if (!translation.empty())
			{
				dictionary[input] = translation;
			}
		}
	}
}