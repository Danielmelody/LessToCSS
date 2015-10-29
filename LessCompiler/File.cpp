#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "regex"
#include "File.h"

using namespace std;
using namespace tr1;

File::File()
{
	split = { ';', '{', '}' };
	blocking = false;
	checkBlockingStart = false;
	checkBlockingEnd = false;
}


File::~File()
{
}

void File::read(string relativePath) {
	ifstream lessStream(relativePath);
	string sentence;
	for (;;) {
		char word = lessStream.get();
		if (EOF == word) {
			break;
		}

		if ('/' == word) {
			if (!blocking) {
				checkBlockingStart = true;
			}
			else{
				if (checkBlockingEnd) {

					sentences.push_back(sentence + "/");
					sentence.clear();
					blocking = false;
					checkBlockingEnd = false;
					continue;
				}
			}
		}
		if ('*' == word) {
			if (checkBlockingStart) {
				blocking = true;
				checkBlockingStart = false;
			}
			if (blocking) {
				checkBlockingEnd = true;
			}
		}

		if (!blocking) {
			if ('\n' != word) {
				sentence += word;
			}
			else {
				sentence.clear();
			}
			if (split.end() != split.find(word)) {
				sentences.push_back(sentence);
				sentence.clear();
			}
		}
		else{
			sentence += word;
		}
	}
	lessStream.close();
	fileName = relativePath.substr(0, relativePath.size() - 5);
}

vector<string>& File::getSentences() {
	return sentences;
}


void File::genarateCSS(map<string, Context*> selectors) {

	int selectorIndex = 0;

	for (auto blockSentence : selectors["root"]->getBlocks(selectorIndex)) {
		css.append(blockSentence + "\n");
	}

	for (auto selector : selectors) {
		int attrIndex = 0;
		string header;
		if (selector.first != "root") {
			header = selector.first + "{\n";
			for (auto blockSentence : selector.second->getBlocks(attrIndex)) {
				header.append(blockSentence + "\n");
			}

			for (auto attribute : selector.second->getAttrs()) {
				attrIndex++;

				header.append(attribute.first + ":" + attribute.second + ";\n");

				for (auto blockSentence : selector.second->getBlocks(attrIndex)) {
					header.append(blockSentence + "\n");
				}
			}
			header.append("}\n");
			css.append(header);
			selectorIndex++;
			for (auto blockSentence : selectors["root"]->getBlocks(selectorIndex)) {
				css.append(blockSentence + "\n");
			}
		}

	}

	ofstream geneStream(fileName + ".css");
	geneStream << css.c_str() << endl;
	geneStream.close();
}