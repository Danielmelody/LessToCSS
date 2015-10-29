#include "stdafx.h"
#include "expression.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int stot(string s) {
	int a = 0, i;
	int l = s.size();
	if (s[0] == '-') {
		for (i = 1; i<l; i++) {
			a = a * 10 + s[i] - '0';
		}
		a *= -1;
	}
	else {
		for (i = 0; i<l; i++) {
			a = a * 10 + s[i] - '0';
		}
	}
	return a;
}
string ttos(int a) {
	string s;
	char s3[100];
	int x, i;
	if (a>0) {
		i = 0; x = a;
		while (x>0) {
			s3[i++] = 'c';
			x /= 10;
		}
		s3[i] = '\0'; x = a;
		while (x>0) {
			s3[--i] = (x % 10 + '0');
			x /= 10;
		}
		s = s3;
	}
	if (a == 0) {
		s = "0";
	}
	if (a<0) {
		s3[0] = 'c';
		i = 1; x = -a;
		while (x>0) {
			s3[i++] = 'c';
			x /= 10;
		}
		s3[i] = '\0'; x = -a;
		while (x>0) {
			s3[--i] = (x % 10 + '0');
			x /= 10;
		}
		s3[0] = '-';
		s = s3;
	}
	return s;
}
int getr(string col) {
	int r = 0;
	if (col[1] >= 'A'&&col[1] <= 'Z')
		r = (col[1] - 'A' + 10) * 16;
	else
		r = (col[1] - '0') * 16;
	if (col[2] >= 'A'&&col[2] <= 'Z')
		r += (col[2] - 'A' + 10) * 16;
	else
		r += (col[2] - '0');
	return r;
}
string setc(int r, int g, int b) {
	string ans = "#111111";
	ans[0] = '#';
	if (r / 16>9)
		ans[1] = r / 16 - 10 + 'A';
	else
		ans[1] = r / 16 + '0';
	if (r % 16>9)
		ans[2] = r % 16 - 10 + 'A';
	else
		ans[2] = r % 16 + '0';
	if (g / 16>9)
		ans[3] = g / 16 - 10 + 'A';
	else
		ans[3] = g / 16 + '0';
	if (g % 16>9)
		ans[4] = g % 16 - 10 + 'A';
	else
		ans[4] = g % 16 + '0';
	if (b / 16>9)
		ans[5] = b / 16 - 10 + 'A';
	else
		ans[5] = b / 16 + '0';
	if (b % 16>9)
		ans[6] = b % 16 - 10 + 'A';
	else
		ans[6] = b % 16 + '0';
	return ans;
}
int getg(string col) {
	int g = 0;
	if (col[3] >= 'A'&&col[3] <= 'Z')
		g = (col[3] - 'A' + 10) * 16;
	else
		g = (col[3] - '0') * 16;
	if (col[4] >= 'A'&&col[4] <= 'Z')
		g += (col[4] - 'A' + 10) * 16;
	else
		g += (col[4] - '0');
	return g;
}
int getb(string col) {
	int b = 0;
	if (col[5] >= 'A'&&col[5] <= 'Z')
		b = (col[5] - 'A' + 10) * 16;
	else
		b = (col[5] - '0') * 16;
	if (col[6] >= 'A'&&col[6] <= 'Z')
		b += (col[6] - 'A' + 10) * 16;
	else
		b += (col[6] - '0');
	return b;
}
string divc(string col, string num) {
	int r, g, b;
	r = g = b = 0;
	int i, n;
	for (i = 1; i <= 6; i++)
		if (col[i] >= 'a'&&col[i] <= 'z')
			col[i] -= 32;
	n = stot(num);
	r = getr(col);
	g = getg(col);
	b = getb(col);
	r /= n;
	b /= n;
	g /= n;
	if (r>255)
		r = 255;
	if (g>255)
		g = 255;
	if (b>255)
		b = 255;
	if (r<0)
		r = 0;
	if (g<0)
		g = 0;
	if (b<0)
		b = 0;
	string ans;
	ans = setc(r, g, b);
	return ans;
}
string powc(string col, string num) {
	int r, g, b;
	r = g = b = 0;
	int i, n;
	for (i = 1; i <= 6; i++)
		if (col[i] >= 'a'&&col[i] <= 'z')
			col[i] -= 32;
	n = stot(num);
	r = getr(col);
	g = getg(col);
	b = getb(col);
	r *= n;
	b *= n;
	g *= n;
	if (r>255)
		r = 255;
	if (g>255)
		g = 255;
	if (b>255)
		b = 255;
	if (r<0)
		r = 0;
	if (g<0)
		g = 0;
	if (b<0)
		b = 0;
	string ans;
	ans = setc(r, g, b);
	return ans;
}
string addc(string col1, string col2) {
	int r, g, b;
	int i;
	for (i = 1; i <= 6; i++) {
		if (col1[i] >= 'a'&&col1[i] <= 'z')
			col1[i] -= 32;
		if (col2[i] >= 'a'&&col2[i] <= 'z')
			col2[i] -= 32;
	}
	r = getr(col1) + getr(col2);
	g = getg(col1) + getg(col2);
	b = getb(col1) + getb(col2);
	if (r>255)
		r = 255;
	if (g>255)
		g = 255;
	if (b>255)
		b = 255;
	if (r<0)
		r = 0;
	if (g<0)
		g = 0;
	if (b<0)
		b = 0;
	string ans;
	ans = setc(r, g, b);
	return ans;
}
string subc(string col1, string col2) {
	int r, g, b;
	int i;
	for (i = 1; i <= 6; i++) {
		if (col1[i] >= 'a'&&col1[i] <= 'z')
			col1[i] -= 32;
		if (col2[i] >= 'a'&&col2[i] <= 'z')
			col2[i] -= 32;
	}
	r = getr(col1) - getr(col2);
	g = getg(col1) - getg(col2);
	b = getb(col1) - getb(col2);
	if (r>255)
		r = 255;
	if (g>255)
		g = 255;
	if (b>255)
		b = 255;
	if (r<0)
		r = 0;
	if (g<0)
		g = 0;
	if (b<0)
		b = 0;
	string ans;
	ans = setc(r, g, b);
	return ans;
}
string adds(string s1, string s2) {
	char s3[200], s4[200];
	string st1, st2;
	int i;
	for (i = 1; i<s2.size(); i++)
		s4[i - 1] = s2[i];
	s4[s2.size() - 1] = '\0';
	for (i = 0; i<s1.size() - 1; i++)
		s3[i] = s1[i];
	s3[s1.size() - 1] = '\0';
	st1 = s3;
	st2 = s4;
	return st1 + st2;
}
string calculate(vector<string>& expression) {
	int l = expression.size();
	int p = 0, i;
	for (i = 0; i<l; i += 2) {
		if (expression[i][0] == '"') {
			p = 1;
			break;
		}
		else if (expression[i][0] == '#') {
			p = 2;
			break;
		}
	}
	if (p == 0) {
		i = 1;
		while (i<l) {
			if (expression[i] == "*") {
				string op1, op2, ans;
				op1 = expression[i - 1];
				op2 = expression[i + 1];
				ans = ttos(stot(op1) * stot(op2));
				expression[i - 1] = ans;
				expression.erase(expression.begin() + i);
				expression.erase(expression.begin() + i);
				i = 1;
				l -= 2;
				/*for (int j=0;j<expression.size();j++)
				cout<<expression[j]<<' ';
				cout<<endl;*/
				continue;
			}
			if (expression[i] == "/") {
				string op1, op2, ans;
				op1 = expression[i - 1];
				op2 = expression[i + 1];
				ans = ttos(stot(op1) / stot(op2));
				expression[i - 1] = ans;
				expression.erase(expression.begin() + i);
				expression.erase(expression.begin() + i);
				i = 1;
				l -= 2;
				/*for (int j=0;j<expression.size();j++)
				cout<<expression[j]<<' ';
				cout<<endl;*/
				continue;
			}
			i += 2;
		}
		string ans = expression[0];
		for (i = 1; i<l; i += 2) {
			if (expression[i] == "+") {
				ans = ttos(stot(ans) + stot(expression[i + 1]));
			}
			else {
				ans = ttos(stot(ans) - stot(expression[i + 1]));
			}
		}
		return ans;
	}
	if (p == 1) {
		string ans;
		ans = expression[0];
		for (i = 2; i<l; i += 2)
			ans = adds(ans, expression[i]);
		return ans;
	}
	if (p == 2) {
		i = 1;
		while (i<l) {
			if (expression[i] == "*") {
				string op1, op2, ans;
				op1 = expression[i - 1];
				op2 = expression[i + 1];
				if (op1[0] == '#'&&op2[0] != '#') {
					ans = powc(op1, op2);
				}
				if (op1[0] != '#'&&op2[0] == '#') {
					ans = powc(op2, op1);
				}
				if (op1[0] != '#'&&op2[0] != '#') {
					ans = ttos(stot(op1) * stot(op2));
				}
				expression[i - 1] = ans;
				expression.erase(expression.begin() + i);
				expression.erase(expression.begin() + i);
				i = 1;
				l -= 2;
				continue;
			}
			if (expression[i] == "/") {
				string op1, op2, ans;
				op1 = expression[i - 1];
				op2 = expression[i + 1];
				if (op1[0] == '#'&&op2[0] != '#') {
					ans = divc(op1, op2);
				}
				if (op1[0] != '#'&&op2[0] == '#') {
					ans = divc(op2, op1);
				}
				if (op1[0] != '#'&&op2[0] != '#') {
					ans = ttos(stot(op1) / stot(op2));
				}
				expression[i - 1] = ans;
				expression.erase(expression.begin() + i);
				expression.erase(expression.begin() + i);
				i = 1;
				l -= 2;
				continue;
			}
			i += 2;
		}
		string ans = expression[0];
		for (i = 1; i<l; i += 2) {
			if (expression[i] == "+") {
				ans = addc(ans, expression[i + 1]);
			}
			else {
				ans = subc(ans, expression[i + 1]);
			}
		}
		return ans;
	}
}
