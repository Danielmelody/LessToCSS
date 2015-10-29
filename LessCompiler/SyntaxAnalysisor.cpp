#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <regex>
#include <sstream>
#include "SyntaxAnalysisor.h"
#include "expression.h"

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

void SyntaxAnalysisor::convertVariables(vector<string> &originExpression, Context* context) {
	for (int index = 0; index < originExpression.size() ; ++index) {
		originExpression[index] = eraseSpace(originExpression[index]);
		if (originExpression[index][0] == '@') {
			originExpression[index] = context->getVariable(originExpression[index]);
			continue;
		}
		string newExpression;
		for (int i = 0; i < originExpression[index].length(); ++i) {
			if (originExpression[index][i] == '=') {
				i++;
				string insideExpression;
				int flag = 0;
				char ch = originExpression[index][i];
				for (; i < originExpression[index].length(); ++i) {
					ch = originExpression[index][i];
					if (ch == '(') { flag++; }
					if (ch == ')') { flag--; }
					if (flag < 0) {
						auto newExpressVector = genExpressVector(insideExpression);
						convertVariables(newExpressVector, context);
						insideExpression = calculate(newExpressVector);
						newExpression.append("=" + insideExpression);
						break;
					}
					insideExpression += ch;
				}
			}
			newExpression += originExpression[index][i];
		}
		originExpression[index] = newExpression;
	}
}

std::string SyntaxAnalysisor::getExpressionValue(std::string expression, Context* context){
	auto expreVector = genExpressVector(expression);
	convertVariables(expreVector, context);
	string value = calculate(expreVector);

	return value;
}

string SyntaxAnalysisor::eraseSpace(string origin) {
	string result;
	for (auto _char : origin) {
		if (_char != ' ' && _char != ';') {
			result += _char;
		}
	}
	return result;
}

vector<string> SyntaxAnalysisor::genExpressVector(string origin) {
	vector<string> result;
	string currentElement;
	for (size_t index = 0; index < origin.size(); ++index) {
		string st = { origin[index] };
		if (st == " " || st == ";") {
			if (currentElement.size() > 0) {
				result.push_back(currentElement);
			}
			currentElement.clear();
		}
		else
		{
			currentElement.append(st);
		}
		
	}
	if (currentElement.size() > 0) {
		result.push_back(currentElement);
	}
	return result;
}

void SyntaxAnalysisor::normalSentence(std::string& sentence) {
	regex colon("[^:]+");
	string attr, expression;
	sregex_iterator iter(sentence.begin(), sentence.end(), colon);
	sregex_iterator end;
	smatch sm1 = *iter;
	attr = sm1.str();
	iter++;
	smatch sm2 = *iter;
	expression = sm2.str();

	attr = eraseSpace(attr);
	Context::current()->setExpression(attr, expression);
	Context::current()->setAttr(attr, getExpressionValue(expression, Context::current()));

}



void SyntaxAnalysisor::varialbleDefinition(std::string & sentence){
	regex colon("[^:]+");
	string key, expression;
	sregex_iterator iter(sentence.begin(), sentence.end(), colon);
	sregex_iterator end;
	smatch sm1 = *iter;
	key = sm1.str();
	iter++;
	smatch sm2 = *iter;
	expression = sm2.str();
	key = eraseSpace(key);
	Context::current()->setExpression(key, expression);
	Context::current()->setVariableInCurrentContext(key, getExpressionValue(expression, Context::current()));
}

void SyntaxAnalysisor::fieldSentence(std::string& sentence) {
	regex inField(".+[\{].*");
	regex outField(".*[\}].*");
	if (regex_match(sentence, inField)) {
		string localName;
		for (auto ch : sentence) {
			
			if ('{' == ch || '(' == ch ) {
				break;
			}

			localName += ch;
			
		}

		localName = eraseSpace(localName);

		Context::setCurrent(Context::current()->getSelectorName() + localName);
		
		return;
	}
	if (regex_match(sentence, outField)) {
		Context::closeCurrent();
		return;
	}
}

void SyntaxAnalysisor::eraseAnno(std::string& sentence) {
	regex anno("//.*");
	sentence = regex_replace(sentence, anno, "");
}

void SyntaxAnalysisor::mixinAfterParsing(std::string sentence){
	regex field(".*[{|}][ ]*");
	regex other("[^:|^\{|^\}]+;");
	if (regex_match(sentence, field)) {
		fieldSentence(sentence);
		return;
	}
	if (regex_match(sentence, other)) {
		mixinSentence(sentence);
	}
}

void SyntaxAnalysisor::parseSentence(std::string sentence) {
	regex field(".*[{|}][ ]*");
	regex normal("[^@]+:.*;");
	regex anno("[ ]*//.*");
	regex blockRe(".*/\\*(.|\r\n|\n)*?\\*/");

	if (regex_match(sentence, blockRe)) {
		Context::current()->registeBlock(sentence);
		return;
	}

	if (regex_match(sentence, anno)) {
		return;
	}
	
	if (regex_match(sentence, field)) {
		fieldSentence(sentence);
		return;
	}

	if (regex_match(sentence, normal)) {
		normalSentence(sentence);
		return;
	}

}

void SyntaxAnalysisor::preBuildVariableField(std::string sentence){
	regex inField(".+[\{].*");
	regex outField(".*[\}].*");
	if (regex_match(sentence, inField)) {
		string localName;
		bool hasArgs = false;
		string args;
		for (auto ch : sentence) {
			if (ch == '(') {
				hasArgs = true;
				continue;
			}
			if (ch == ')') {
				break;
			}
			if (hasArgs) {
				args += ch;
			}
			if ('{' == ch) {
				break;
			}
			if (' ' != ch && !hasArgs) {
				localName += ch;
			}
		}
		new Context(Context::current(), localName);
		if (hasArgs) {
			
			Context::current()->setArgs(handleAttrs(args));
		}
		return;
	}
	if (regex_match(sentence, outField)) {
		Context::closeCurrent();
		return;
	}
}

void SyntaxAnalysisor::mixinSentence(std::string sentence){
	sentence = eraseSpace(sentence);
	regex hasArgs(".+[\(].*[\)]");
	if (regex_match(sentence, hasArgs)) {
		regex colon("[^(\(|\))]+");
		string other, attrs;
		sregex_iterator iter(sentence.begin(), sentence.end(), colon);
		sregex_iterator end;
		smatch sm1 = *iter;
		other = sm1.str();
		iter++;
		smatch sm2 = *iter;
		attrs = sm2.str();
		other = eraseSpace(other);
		Context::selectors[other]->passArgs(handleRealArgs(attrs));
		Context::selectors[other]->calculateAllExpression(Context::selectors[other]);
		Context::current()->mixin(other);
	}
	else
	{
		Context::current()->mixin(sentence);
	}
}

vector<string> SyntaxAnalysisor::handleRealArgs(std::string attrs)
{
	vector<string> valueVec;
	string expression;
	for (auto ch : attrs) {
		if (ch != ',') {
			expression += ch;
		}
		else {
			expression = eraseSpace(expression);
			valueVec.push_back(expression);
			expression.clear();
		}
	}
	expression = eraseSpace(expression);
	valueVec.push_back(expression);
	expression.clear();
	return valueVec;
}

vector<pair<string, string>> SyntaxAnalysisor::handleAttrs(std::string attrs){
	vector<string> expreVector;
	string expression;
	for (auto ch : attrs){
		if (ch == ',') {
			if (expression.size() > 0) {
				expression = eraseSpace(expression);
				expreVector.push_back(expression);
				expression.clear();
			}
		}
		else{
			expression += ch;
		}
	}

	if (expression.size() > 0) {
		expression = eraseSpace(expression);
		expreVector.push_back(expression);
		expression.clear();
	}

	vector<pair<string, string>> attrsVector;
	for each (string expre in expreVector){
		regex colon("[^:]+");
		string key, value;
		sregex_iterator iter(expre.begin(), expre.end(), colon);
		sregex_iterator end;
		smatch sm1 = *iter;
		key = sm1.str();
		iter++;
		smatch sm2 = *iter;
		value = sm2.str();
		attrsVector.push_back(pair<string, string>(key, value));
	}
	Context::current()->calculateAllExpression(Context::current());
	return attrsVector;
}

map<string, string> SyntaxAnalysisor::genArgMap(vector<pair<string, string>> argVec)
{
	map<string, string> result;
	for (auto argPair : argVec) {
		if (argPair.second != "" && argPair.first != "") {
			result[argPair.first] = argPair.second;
		}
	}
	return result;
}

void SyntaxAnalysisor::buildVariableSystem(std::string sentence)
{
	regex varial("[ ]*@.+:.+;");
	regex field(".*[{|}][\s]*");

	

	if (regex_match(sentence, varial)) {
		varialbleDefinition(sentence);
		return;
	}

	if (regex_match(sentence, field)) {
		preBuildVariableField(sentence);
		return;
	}

}
