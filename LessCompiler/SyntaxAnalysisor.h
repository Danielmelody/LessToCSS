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
	/** SyntaxAnalysisor::convertVariables
	
	* @note: convert all variables into it's value in a expression
	* @return:   void
	* @param:    std::vector<string> & originExpression
	* @param:    Context * context
	*/
	static void convertVariables(std::vector<string>& originExpression, Context* context);
	/** SyntaxAnalysisor::normalSentence
	
	* @note:    handle attributes setting
	* @return:   void
	* @param:    std::string & sentence
	*/
	static void normalSentence(std::string& sentence);
	/** SyntaxAnalysisor::varialbleDefinition
	
	* @note:    define variable and init it
	* @return:   void
	* @param:    std::string & sentence
	*/
	static void varialbleDefinition(std::string& sentence);

	/** SyntaxAnalysisor::fieldSentence
	
	* @note:    field sentence usually contains a character like '{' or '}'
					which decide whether it should be poped or pushed
	* @return:   void
	* @param:    std::string & sentence
	*/
	static void fieldSentence(std::string& sentence);
	/** SyntaxAnalysisor::eraseAnno
	
	* @return:   void
	* @param:    std::string & sentence
	*/
	static void eraseAnno(std::string& sentence);
	/** SyntaxAnalysisor::preBuildVariableField
	
	* @note:   only call before normal Analysis 
	* @return:   void
	* @param:    std::string sentence
	*/
	static void preBuildVariableField(std::string sentence);

	/** SyntaxAnalysisor::mixinSentence
	
	* @note:   called after normal analysis, do the real mixin
	* @return:   void
	* @param:    std::string sentence
	*/
	static void mixinSentence(std::string sentence);
	/** SyntaxAnalysisor::handleRealArgs
	
	* @note:    pass real args to another context
	* @return:   vector<string>
	* @param:    std::string attrs
	*/
	static vector<string> handleRealArgs(std::string attrs);
	/** SyntaxAnalysisor::handleAttrs
	
	* @note:     preset args order and default value before mixin
	* @return:   vector<pair<string, string>>
	* @param:    std::string attrs
	*/
	static vector<pair<string, string> > handleAttrs(std::string attrs);
	/** SyntaxAnalysisor::genArgMap
	
	* @note:    convert args vector to map
	* @return:   map<string, string>
	* @param:    vector<pair<string
	* @param:    string>> argVec
	*/
	static map<string, string> genArgMap(vector<pair<string, string>  > argVec);
public:
	/** SyntaxAnalysisor::eraseSpace
	
	* @return:   std::string
	* @param:    std::string origin
	*/
	static std::string eraseSpace(std::string origin);
	/** SyntaxAnalysisor::getExpressionValue

	* @return:   std::string
	* @param:    std::string expression
	* @param:    Context * context
	*/
	static std::string getExpressionValue(std::string expression, Context* context);
	
	/** SyntaxAnalysisor::mixinAfterParsing
	
	* @return:   void
	* @param:    std::string sentence
	*/
	static void mixinAfterParsing(std::string sentence);
	/** SyntaxAnalysisor::parseSentence
	
	* @return:   void
	* @param:    std::string sentence
	*/
	/** SyntaxAnalysisor::parseSentence
	
	* @note:   normal parsing
	* @return:   void
	* @param:    std::string sentence
	*/
	static void parseSentence(std::string sentence);
	/** SyntaxAnalysisor::buildVariableSystem
	
	* @note:    before normal parsing
	* @return:   void
	* @param:    std::string sentence
	*/
	static void buildVariableSystem(std::string sentence);
	SyntaxAnalysisor();
	~SyntaxAnalysisor();
};

