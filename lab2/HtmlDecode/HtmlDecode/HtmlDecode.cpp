#include <iostream>
#include <map>
#include <string>

using namespace std;


//��������� ������ ���������� ������ � ������������� ����� ctrl+z ���� ����� ������

//������ ���� ����������� � �������� �� vector
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
			//�� ������������ substr ������������ append
			result += html.substr(i);
			break;
		}

		//�� ������������ substr ������������ append
		result += html.substr(i, position - i);

		//����� �������� ����� ��������
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