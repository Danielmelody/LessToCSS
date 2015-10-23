// Trying.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <regex>
#include <vector>
#include <sstream>
#include <set>

using namespace std::tr1;
using namespace std;

int main()
{
	const std::tr1::regex selector("([a-z]|[1-9]|[A-Z]|_)+:");
	const std::tr1::regex expresionRe(":[^;]+;");
	const std::tr1::regex variable("@([a-z]|[1-9]|[A-Z]|_)+");

	/*
	std::string sentence;
	std::sregex_token_iterator iter(sentence.begin(), sentence.end(), variable);
	std::sregex_token_iterator end;
	for (iter; iter != end; ++iter){

	}
	*/

	regex anno("//.*");
	string sentence = regex_replace("bchjdbhak//cdysgyuay", anno, "");
	cout << sentence;
	
	system("PAUSE");
    return 0;
}

