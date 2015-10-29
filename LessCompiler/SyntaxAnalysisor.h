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
	static std::vector<std::string> genExpressVector(std::string origin);
	static void convertVariables(std::vector<string>& originExpression, Context* context);
	static void normalSentence(std::string& sentence);
	static void varialbleDefinition(std::string& sentence);
	static void fieldSentence(std::string& sentence);
	static void eraseAnno(std::string& sentence);
	static void preBuildVariableField(std::string sentence);
	static void mixinSentence(std::string sentence);
	static vector<string> handleRealArgs(std::string attrs);
	static vector<pair<string, string>> handleAttrs(std::string attrs);
	static map<string, string> genArgMap(vector<pair<string, string>> argVec);
public:
	static std::string eraseSpace(std::string origin);
	static std::string getExpressionValue(std::string expression, Context* context);
	static void mixinAfterParsing(std::string sentence);
	static void parseSentence(std::string sentence);
	static void buildVariableSystem(std::string sentence);
	SyntaxAnalysisor();
	~SyntaxAnalysisor();
};

