#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "File.h"
#include "SyntaxAnalysisor.h"

int main()
{
	File file;
	Context::root();
	file.read("test.less");
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

	for (auto selector : Context::selectors) {
		cout << selector.first.c_str();
	}

	file.genarateCSS(Context::selectors);
	system("PAUSE");
    return 0;
}

