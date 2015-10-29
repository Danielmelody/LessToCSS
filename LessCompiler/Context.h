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

	static std::map<string, Context*> selectors;

	/** Context::registeBlock
	
	* @note:   saving block annotation
	* @return:   void
	* @param:    string blockCont
	*/
	void registeBlock(string blockCont);

	/** Context::calculateAllExpression
	
	* @note:
	* @return:   void
	* @param:    Context * beMixing
	*/
	void calculateAllExpression(Context* beMixing);

	/** Context::getBlocks
	
	* @note:
	* @return:   vector<string>
	* @param:    int index
	*/
	vector<string> getBlocks(int index);

	/** Context::setExpression
	
	* @note:  save the origin expression so when variables changed ,the expression value changed 
	* @return:   void
	* @param:    string key
	* @param:    string value
	*/
	void setExpression(string key, string value);

	/** Context::passArgs
	
	* @note:    passing real args when mixin
	* @return:   void
	* @param:    vector<string> realArgs
	*/
	void passArgs(vector<string> realArgs);
	
	/** Context::setArgs
	
	* @note:    set formal args
	* @return:   void
	* @param:    vector<pair<string
	* @param:    string>> args
	*/
	void setArgs(vector<pair<string, string>> args);
	/** Context::mixin
	
	* @note:
	* @return:   void
	* @param:    string otherSelector
	*/
	void mixin(string otherSelector);
	/** Context::preHandleMixinVariable
	
	* @note:
	* @return:   void
	* @param:    string otherSelector
	* @param:    vector<string> args
	*/
	void preHandleMixinVariable(string otherSelector, vector<string> args);
	
	/** Context::getSelectorName

	* @return:   std::string
	*/
	string getSelectorName();
	/** Context::setVariableInCurrentContext
	
	* @note:
	* @return:   void
	* @param:    string key
	* @param:    string value
	*/
	void setVariableInCurrentContext(string key, string value);
	/** Context::setAttr
	
	* @note:    set variables only in current whether it's parents has or not,
				parents' will not be overwrite;
	* @return:   void
	* @param:    string key
	* @param:    string value
	*/
	void setAttr(string key, string value);
	/** Context::getVariable
	
	* @note:
	* @return:   std::string
	* @param:    string key
	*/
	string getVariable(string key);
	/** Context::getAttr
	
	* @note:
	* @return:   std::string
	* @param:    string key
	*/
	string getAttr(string key);
	/** Context::getAttrs
	
	* @note:
	* @return:   map<string, string>&
	*/
	map<string, string>& getAttrs();

	static Context* closeCurrent();
	static Context* current();
	static void setCurrent(string fullName);
	static  Context* root();

	Context(Context* parent, string localName);
	~Context();
};

