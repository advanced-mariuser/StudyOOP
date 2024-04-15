#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

using Dictionary = map<string, vector<string>>;

void LoadDictionary(const string& filename, Dictionary& dictionary);

void SaveDictionary(const string& filename, const Dictionary& dictionary);

void SaveChanges(const string& dictionary_filename, const Dictionary& dictionary);

void RunDictionaryProgram(Dictionary& dictionary);