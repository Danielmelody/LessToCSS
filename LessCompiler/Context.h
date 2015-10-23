#pragma once

#include <iostream>
#include <map>
#include <set>

using namespace std;

class Context{

private:
	Context();
	Context* _parent = nullptr;
	string _fullName;
	static Context* _current,* _root;
	map<string, string> _variables, _attrs;
	string getVariableInCurrentContext(string key);
	void setVariableInCurrentContext(string key, string value);
	
public:

	static string parseElement(string element);
	static std::map<string, Context*> selectors;
	static Context* closeCurrent();
	static Context* current();
	static  Context* root();
	string getSelectorName();
	void setAttr(string key, string value);
	void setVariable(string key, string value);
	string getVariable(string key);
	string getAttr(string key);
	map<string, string>& getAttrs();
	Context(Context* parent, string localName);
	~Context();
};

