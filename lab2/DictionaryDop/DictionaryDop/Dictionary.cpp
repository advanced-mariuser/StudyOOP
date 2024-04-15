#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using Dictionary = map<string, vector<string>>;

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
		size_t delimiter_pos = line.find(':');
		if (delimiter_pos != string::npos)
		{
			string key = line.substr(0, delimiter_pos);
			string values = line.substr(delimiter_pos + 1);

			size_t start_pos = 0;
			size_t comma_pos = values.find(',');
			int size = 0;
			while (comma_pos != string::npos)
			{
				size++;
				start_pos = comma_pos + 1;
				comma_pos = values.find(',', start_pos);
			}
			size++;

			vector<string> value_vector;
			start_pos = 0;
			comma_pos = values.find(',');
			for (int i = 0; i < size; i++)
			{
				string value = values.substr(start_pos, comma_pos - start_pos);
				value_vector.push_back(value);
				start_pos = comma_pos + 1;
				comma_pos = values.find(',', start_pos);
			}

			dictionary[key] = value_vector;
		}
	}

	file.close();
}

void SaveDictionary(const string& dictionary_filename, const Dictionary& dictionary)
{
	ofstream file(dictionary_filename);
	if (!file.is_open())
	{
		throw invalid_argument("Failed to open output file");
	}

	for (const auto& pair : dictionary)
	{
		file << pair.first << ":";
		const vector<string>& values = pair.second;
		for (size_t i = 0; i < values.size(); ++i)
		{
			file << values[i];
			if (i != values.size() - 1)
			{
				file << ", ";
			}
		}
		file << endl;
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

		auto it = dictionary.find(input);
		if (it != dictionary.end())
		{
			cout << "Translations for '" << input << "': ";
			const vector<string>& translations = it->second;
			for (const auto& translation : translations)
			{
				cout << translation << " ";
			}
			cout << endl;
		}
		else
		{
			cout << "Enter translation(s) for '" << input << "' separated by spaces: ";
			string translations_input;
			getline(cin, translations_input);

			// Разбиваем ввод пользователя на отдельные переводы
			size_t start_pos = 0;
			size_t space_pos = translations_input.find(' ');
			vector<string> translations;
			while (space_pos != string::npos)
			{
				string translation = translations_input.substr(start_pos, space_pos - start_pos);
				translations.push_back(translation);
				start_pos = space_pos + 1;
				space_pos = translations_input.find(' ', start_pos);
			}
			// Добавляем последний перевод в вектор
			string last_translation = translations_input.substr(start_pos);
			translations.push_back(last_translation);

			// Добавляем каждый перевод в словарь как значение для введенного слова
			dictionary[input] = translations;
			for (const auto& translation : translations)
			{
				dictionary[translation] = vector<string>{ input + ", " };
			}
		}
	}
}