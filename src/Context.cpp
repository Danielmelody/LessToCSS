#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <regex>
#include "Context.h"
#include "SyntaxAnalysisor.h"

using namespace std;

map<string, Context*> Context::selectors;

Context* Context::_root;
Context* Context::_current;
map<string, map<string, string> > Context::_variables;

Context::Context() {
	_parent = nullptr;
	selectors["root"] = this;
	_fullName = "";
	_variables[_fullName] = map<string, string>();
}

Context::Context(Context* parent, string localName){
	_parent = parent;
	_fullName = _parent->getSelectorName() + localName;
	_fullName = SyntaxAnalysisor::eraseSpace(_fullName);
	selectors[_fullName] = this;
	_current = this;
	_attrs.clear();
	_variables[_fullName] = map<string, string>();
}


Context::~Context()
{
	
}

Context * Context::closeCurrent()
{
	_current = _current->_parent;
	return _current;
}

Context* Context::current() {
	return _current;
}

void  Context::setCurrent(string fullName){
	if (fullName == "") {
		_current = selectors["root"];
	}
	else{
		_current = selectors[fullName];
	}
}

Context* Context::root() {
	if (_root == nullptr) {
		_root = new Context();
		_current = _root;
	}
	return _root;
}


void Context::setArgs(vector<pair<string, string> > args){
	_args = args;
	for (auto argPair : args) {
		_expressions[argPair.first] = argPair.second;
	}
	calculateAllExpression(this);
}

void Context::mixin(string otherSelector){

	auto other = selectors[otherSelector];

	auto otherAttrs = other->getAttrs();
	
	for (auto attr : otherAttrs) {
		setAttr(attr.first, attr.second);
	}

}

void Context::preHandleMixinVariable(string otherSelector, vector<string> args)
{
	for (int i = 0; i < args.size(); ++i) {
		selectors[otherSelector]->setVariableInCurrentContext(_args[i].first, args[i]);
	}
}

string Context::getSelectorName() {
	return _fullName;
}

string Context::getVariableInCurrentContext(string key) {

	auto reIterate = _variables[_fullName].find(key);
	
	if (_variables[_fullName].end() != reIterate) {
		return reIterate->second;
	}
	return "";
	
	
}

void Context::registeBlock(string blockContent){
	int index = _attrs.size();
	if (this == _root) {
		index = selectors.size()-1;
		int i = 0;
	}
	if (_blocks.end() == _blocks.find(index)) {
		_blocks[index] = vector<string>();
	}
	_blocks[index].push_back(blockContent);
}

void Context::calculateAllExpression(Context* beMixing)
{
	for (auto exPair : _expressions) {

		string value = SyntaxAnalysisor::getExpressionValue(exPair.second, beMixing);
		if (exPair.first[0] == '@') {
			beMixing->_variables[_fullName][exPair.first] = value;
		}
		else
		{
			beMixing->_attrs[exPair.first] = value;
		}
	}
}

vector<string> Context::getBlocks(int index){
	auto result = _blocks.find(index);
	if (_blocks.end() != _blocks.find(index)) {
		return result->second;
	}
	return vector<string>();
}

void Context::setExpression(string key, string value){
	_expressions[key] = value;
}

void Context::passArgs(vector<string> realArgs){
	for (int i = 0; i < realArgs.size(); ++i) {
		auto first = _args[i].first;
		setVariableInCurrentContext(first, realArgs[i]);
		_expressions[first] = realArgs[i];
	}
	calculateAllExpression(this);
}



void Context::setVariableInCurrentContext(string key, string value) {
	_variables[_fullName][key] = value;
}


string Context::getVariable(string key) {
	Context* context = this;
	string result;
	while (context) {
		result = context->getVariableInCurrentContext(key);
		if ("" != result) {
			break;
		}
		context = context->_parent;
	}
	return result;
}

void Context::setAttr(string key, string value) {
	_attrs[key] = value;
}

string Context::getAttr(string key) {
	try
	{
		return _attrs.at(key);
	}
	catch (const std::out_of_range&)
	{
		return "";
	}
}

map<string, string>& Context::getAttrs() {
	return _attrs;
}