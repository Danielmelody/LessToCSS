#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <regex>


class SyntaxAnalysisor;

#include "Context.h"

class SyntaxAnalysisor
{
private:
	static std::string block;
	static int blockNum;
	static std::set<char> split;
	static std::vector<std::string>& genExpressVector(std::string noSpaceString);
	static std::string& eraseSpace(std::string origin);
	static void convertVariables(std::string& originExpression);
	static void normalSentence(std::string& sentence);
	static void fieldSentence(std::string& sentence);
	static void registerBlock();
	static void eraseAnno(std::string& sentence);
public:
	static void parseSentence(std::string sentence);
	SyntaxAnalysisor();
	~SyntaxAnalysisor();
};

