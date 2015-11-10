#pragma once
#include <iostream>
#include <map>
#include <set>
#include <vector>

class File;

#include "Context.h"


class File
{
private:
	bool checkBlockingStart;
	bool checkBlockingEnd;
	bool blocking;
	std::set<char> split;
	std::string fileName;
	std::string contents;
	std::string css;
	std::vector<std::string> sentences;
public:
	/** File::read
	
	* @note:  read a *.less from giving relative path, print content to variable contents
	* @return:   void
	* @param:    std::string relativePath
	*/
	void read(std::string relativePath);

	/** File::getSentences
	
	* @note:  convert contents to less sentences:eg. width:80px;
	* @return:   std::vector<std::string>&
	*/
	std::vector<std::string>& getSentences();

	/** File::genarateCSS

	* @note:     generate a *.css file with the name of *less just readed;
	* @return:   void
	* @param:    std::map<string
	* @param:    Context * > selectors
	*/
	void genarateCSS(std::map<string, Context*> selectors);
	
	File();
	~File();
};

