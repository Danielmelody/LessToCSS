#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "File.h"
#include "SyntaxAnalysisor.h"
#include <regex>

using namespace std;

int main(int argc,char *argv[])
{
	string fileName;
	if(argc > 1){
		fileName = string(argv[1]);
	
		File file;
		Context::root();
		file.read(fileName);
		cout<<fileName<<endl;
		for (auto sentence : file.getSentences()) {
		//cout << sentence << endl;
			SyntaxAnalysisor::buildVariableSystem(sentence);
		}
		for (auto sentence : file.getSentences()) {
		//cout << sentence << endl;
			SyntaxAnalysisor::parseSentence(sentence);
		}
		
		for (auto sentence : file.getSentences()) {
			SyntaxAnalysisor::mixinAfterParsing(sentence);
		}

		file.genarateCSS(Context::selectors);
	}
	else{
		cout<<"usage: toCSS <file name>.less"<<endl;
	}

    return 0;
}

