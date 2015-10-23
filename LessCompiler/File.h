#pragma once
#include <iostream>
#include <map>
#include <set>
#include <vector>

class File;

#include "Context.h"


class File
{
private:
	bool checkBlockingStart;
	bool checkBlockingEnd;
	bool blocking;
	std::set<char> split;
	std::string fileName;
	std::string contents;
	std::string css;
	std::vector<std::string> sentences;
public:
	void read(std::string relativePath);

	std::vector<std::string>& getSentences();

	void genarateCSS(std::map<string, Context*> selectors);
	
	File();
	~File();
};

