#include<iostream>
#include<string>
#include<vector>
#include"InfoExtract.h"
using namespace std;
string::size_type pos(string mainstr, char subch);
bool in(string substr, string prtstr);
string extract(string rawstr, string::size_type beg, string::size_type en);
vector<string> infoex(string line, char tabch, vector<string> sargv);

vector<string> infoex(string line, char tabch, vector<string> sargv)
{
	vector<string> raw_pdt;
	//分割原始单行数据，按tab分割
	for (string::size_type pre = 0, expl = 0; expl != line.size(); ++expl) {
		if (line[expl] == tabch) {
			raw_pdt.push_back(extract(line, pre, expl));
			pre = expl + 1;
		}
	}
	//根据关键词提取raw_pdt中有效信息
	vector<string> mid_pdt;
	for (vector<string>::iterator it = sargv.begin(); it != sargv.end(); it++) {
		for (vector<string>::iterator jt = raw_pdt.begin(); jt != raw_pdt.end(); ++jt) {
			if (in(*it, *jt)) mid_pdt.push_back(extract(*jt, pos(*jt, ':')+1, (*jt).size()));
		}
	}
	return mid_pdt;
}

string extract(string rawstr, string::size_type beg, string::size_type en)
{
	string prodt = "";
	for (string::size_type st = beg; st != en; ++st) {
		prodt += rawstr[st];
	}
	return prodt;
}

//whether str1 is in the str2
//str2 is longer than str1
bool in(string substr, string prtstr)
{
	for (string::size_type ix = 0; ix != substr.size(); ++ix) {
		if (substr[ix] != prtstr[ix]) return 0;
	}
	return 1;
}

//pos func:find the position the char in the string
string::size_type pos(string mainstr, char subch)
{
	for (string::size_type iy = 0; iy != mainstr.size(); ++iy) {
		if (mainstr[iy] == subch) return iy;
	}
	return 0;
}