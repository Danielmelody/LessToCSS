#pragma once

#include <iostream>
#include <map>
#include <set>

using namespace std;

class Context{

private:
	Context();
	Context* _parent = nullptr;
	Context* _bottom = nullptr;
	string _fullName;
	static Context* _current,* _root;
	static map<string, map<string, string>> _variables;
	map<string, string> _attrs;
	map<string, string> _expressions;
	vector<pair<string, string>> _args;
	map<int, vector<string>> _blocks;
	string getVariableInCurrentContext(string key);
	
public:

	void registeBlock(string blockCont);

	void calculateAllExpression(Context* beMixing);

	vector<string> getBlocks(int index);

	void setExpression(string key, string value);

	void passArgs(vector<string> realArgs);

	static std::map<string, Context*> selectors;
	static Context* closeCurrent();
	static Context* current();
	static void setCurrent(string fullName);
	static  Context* root();
	
	void setArgs(vector<pair<string, string>> args);
	void mixin(string otherSelector);
	void preHandleMixinVariable(string otherSelector, vector<string> args);
	string getSelectorName();
	void setVariableInCurrentContext(string key, string value);
	void setAttr(string key, string value);
	string getVariable(string key);
	string getAttr(string key);
	map<string, string>& getAttrs();
	Context(Context* parent, string localName);
	~Context();
};

