#include <iostream>
#include <map>
#include <string>

using namespace std;


//программа должна продолжать диалог с пользователем через ctrl+z ввод конца строки

//должен быть константным и поменять на vector
map<string, string> HtmlDictionary = {
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" },
};

string HtmlDecode(string const& html)
{
	string result;
	size_t i = 0;

	while (i < html.length())
	{
		size_t position = html.find('&', i);

		if (position == string::npos)
		{
			//не использовать substr использовать append
			result += html.substr(i);
			break;
		}

		//не использовать substr использовать append
		result += html.substr(i, position - i);

		//будет работать долго ускорить
		size_t sec_pos = html.find(';', position);

		if (sec_pos == string::npos)
		{
			result += html.substr(position);
			break;
		}

		string key = html.substr(position, sec_pos - position + 1);

		if (HtmlDictionary.find(key) != HtmlDictionary.end())
		{
			result += HtmlDictionary[key];
			i = sec_pos + 1;
			continue;
		}

		result += html[position];
		i = position + 1;
	}

	return result;
}