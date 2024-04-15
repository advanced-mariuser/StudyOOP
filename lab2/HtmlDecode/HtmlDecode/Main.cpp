#include <iostream>
#include <string>
#include "HtmlDecode.h"

using namespace std;

int main()
{
	try
	{
		cout << "Enter html code" << endl;
		string inputString;
		getline(cin, inputString);

		string outputString = HtmlDecode(inputString);
		cout << outputString << endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}