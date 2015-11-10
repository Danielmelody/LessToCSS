#include <string>
#include <iostream>
#include <vector>

using namespace std;


int stot(std::string s);
string ttos(int a);
int getr(string col);
string setc(int r, int g, int b);
int getg(string col);
int getb(string col);
string powc(string col, string num);
string addc(string col1, string col2);
string subc(string col1, string col2);
string adds(string s1, string s2);
string calculate(vector<string>& expression);