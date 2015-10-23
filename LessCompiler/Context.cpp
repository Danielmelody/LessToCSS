#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <regex>
#include "Context.h"

using namespace std;

map<string, Context*> Context::selectors;

Context* Context::_root;
Context* Context::_current;

Context::Context() {
	_parent = nullptr;
	_fullName = "";
}

Context::Context(Context* parent, string localName){
	_parent = parent;
	_fullName = _parent->getSelectorName() + localName;
	selectors[_fullName] = this;
	_current = this;
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
	_current = _root;
	return _current;
}

Context* Context::root() {
	if (_root == nullptr) {
		_root = new Context();
		_current = _root;
	}
	return _root;
}

string Context::getSelectorName() {
	return _fullName;
}

string Context::getVariableInCurrentContext(string key) {
	try
	{
		string result = _variables.at(key);
		return result;
	}
	catch (const std::out_of_range& e)
	{
		return "";
	}
	
}

string Context::parseElement(string element) {
	if (element[0] == '@') {
		string value = _current->getVariable(element);
		if ("" == value) {
			_current->setVariableInCurrentContext(element, "");
		}
		return value;
	}
	return element;
}

void Context::setVariableInCurrentContext(string key, string value) {
	_variables[key] = value;
}

void Context::setVariable(string key, string value) {
	Context* context = this;
	while (context->_parent) {
		if (context->getVariableInCurrentContext(key) != "") {
			break;
		}
		context = context->_parent;
	}
	if (context != root()) {
		context->setVariableInCurrentContext(key, value);
	}
	else {
		this->setVariableInCurrentContext(key, value);
	}
}

string Context::getVariable(string key) {
	Context* context = this;
	while (context->_parent) {
		string result = context->getVariableInCurrentContext(key);
		if ("" != result) {
			return result;
		}
		context = context->_parent;
	}
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