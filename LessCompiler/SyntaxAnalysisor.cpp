#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <regex>
#include <sstream>
#include "SyntaxAnalysisor.h"

using namespace std;
using namespace std::tr1;

SyntaxAnalysisor::SyntaxAnalysisor()
{
}


SyntaxAnalysisor::~SyntaxAnalysisor()
{
}

set<char> SyntaxAnalysisor::split = { '+','-','/','*','(',')' };
string SyntaxAnalysisor::block;
int SyntaxAnalysisor::blockNum = 0;

void SyntaxAnalysisor::convertVariables(std::string &originExpression) {
	
}

string& SyntaxAnalysisor::eraseSpace(string origin) {
	string result;
	for (auto _char : origin) {
		if (_char != ' ') {
			result += _char;
		}
	}
	return result;
}

vector<string>& SyntaxAnalysisor::genExpressVector(string noSpaceString) {
	vector<string> result;
	string currentElement;
	for (size_t index = 0; index < noSpaceString.size(); ++index) {
		string st = { noSpaceString[index] };

		if (split.end() != split.find(noSpaceString[index])) {
			if (!currentElement.empty()) {
				result.push_back(currentElement);
			}
			currentElement.clear();
			result.push_back(st);
			continue;
		}
		currentElement += noSpaceString[index];
	}
	return result;
}

void SyntaxAnalysisor::normalSentence(std::string& sentence) {
	regex colon("[^:]+");
	string attrOrValue, expression;
	sregex_iterator iter(sentence.begin(), sentence.end(), colon);
	sregex_iterator end;
	smatch sm1 = *iter;
	attrOrValue = sm1.str();
	iter++;
	smatch sm2 = *iter;
	expression = sm2.str();

	

}

void SyntaxAnalysisor::fieldSentence(std::string& sentence) {
	regex inField(".+[\{].*");
	regex outField(".*[\}].*");
	if (regex_match(sentence, inField)) {
		string localName;
		for (auto ch : sentence) {
			if ('{' == ch) {
				break;
			}
			if (' ' != ch) {
				localName += ch;
			}
		}
		Context(Context::current(), localName);
	}
	if (regex_match(sentence, outField)) {
		Context::closeCurrent();
	}
}

void SyntaxAnalysisor::eraseAnno(std::string& sentence) {
	regex anno("//.*");
	sentence = regex_replace(sentence, anno, "");
}

void SyntaxAnalysisor::registerBlock() {
	stringstream sindex;
	sindex << blockNum;
	Context::current()->setAttr("block" + sindex.str(), block);
	block.clear();
}

void SyntaxAnalysisor::parseSentence(std::string sentence) {
	regex field(".*[{|}][ ]*");
	regex normal("[^@]+:.*;");
	regex varial("@.+:.+;");
	regex anno("[ ]*//.*");

	regex blockRe("/[\*].*[\*]/");

	if (regex_match(sentence, blockRe)) {
		blockNum++;
		registerBlock();
		return;
	}

	if (regex_match(sentence, anno)) {
		return;
	}
	
	if (regex_match(sentence, field)) {
		fieldSentence(sentence);
		return;
	}

	if (regex_match(sentence, varial)) {
		
	}

	if (regex_match(sentence, normal)) {
		normalSentence(sentence);
		return;
	}
	

}
