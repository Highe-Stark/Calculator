#pragma once

#include<string>
#include<vector>
#include"Function.h"
using std::vector;
using std::string;
double M;


class Token
{
public:
	//represent the catagory the token belongs
	//if operand->the token.ctg store the operand, leaving the value empty;
	//else token.ctg = 8, means the value is a number;
	char ctg;
	double value;
	Token() {}
	Token(char ch, double v): ctg(ch), value(v) {}
};

class TokenStream
{

public:
	vector<Token> token_stream;
	vector<Token>::size_type point;

	//    >TokenStream can't be copied;
	TokenStream(const TokenStream& other) = delete;
	TokenStream& operator=(const TokenStream& other) = delete;

	//    >construct token stream using a string
	TokenStream(string &instr):point(0)
	{
		
		string::size_type ix = 0;
		while (ix != instr.size()) {
			switch (instr[ix]) {
			case '1':case '2':case '3':case '4':case '5':
			case '6':case '7':case '8':case '9':case '0':
			{	string::size_type iy = ix + 1;
				while (instr[iy] == '1' || instr[iy] == '2' || instr[iy] == '3' || instr[iy] == '4' ||
					instr[iy] == '5' || instr[iy] == '6' || instr[iy] == '7' || instr[iy] == '8' ||
					instr[iy] == '9' || instr[iy] == '0' || instr[iy] == '.') ++iy;
				double temp_val = stod(extract(instr, ix, iy));
				Token temp_tok = { '8', temp_val };
				token_stream.push_back(temp_tok);
				ix = iy;
				break;
			}
			case '+':case '-':case '*':case '/':case '(':case ')':case '%':case '!':
			{	Token temp_tok(instr[ix], 0);
				token_stream.push_back(temp_tok);
				++ix;
				break;
			}
			case 's': {
				if (instr[ix + 1] == 'q' && instr[ix + 2] == 'r' && instr[ix + 3] == 't') {
					Token temp_tok('s', 0);
					token_stream.push_back(temp_tok);
					ix += 4;
					break;
				}}
			case ' ':case '\t':
				++ix;
				break;
			case 'M':
				if (ix == instr.size() - 1) {
					ix++;
					break;
				}
				else throw runtime_error("M Invalid use");
			case 'R': {
				Token temp_token('8', M);
				token_stream.push_back(temp_token);
				++ix;
				break; 
			}
			default:
				ix++;
			}
		}
	}
	//func con_stream ends.
	bool eof()
	{
		if (point == token_stream.size())  //point == token_stream.size() - 1
			return true;
		else return false;
	}
};

Token get_token(TokenStream& ts);
void put_back(TokenStream& ts);


Token get_token(TokenStream& ts)
{
	return ts.token_stream[ts.point++];
}

void put_back(TokenStream& ts)
{
	ts.point--;
}
