#pragma once
#ifndef GRAMMER_H
#define GRAMMER_H

#include <iostream>
#include <stdexcept>
#include <math.h>
#include "Grammer.h"
#include "Token.h"
#include "Function.h"
using std::cout;
using std::endl;
using std::runtime_error;

double Expression(TokenStream &ts);
double Term(TokenStream& ts);
double Primary(TokenStream &ts);

double Expression(TokenStream &ts)
{
	double left = Term(ts);
	if (ts.eof()) return left;
	Token t = get_token(ts);
	while (true) {
		if (ts.eof()) {
			put_back(ts);
			return left;
		}
		switch (t.ctg) {
		case '+':
			left += Term(ts);
			if (ts.eof()) return left;
			t = get_token(ts);
			break;
		case '-':
			left -= Term(ts);
			if (ts.eof()) return left;
			t = get_token(ts);
			break;
		default:
			put_back(ts);
			return left;
		}
	}
}

double Term(TokenStream& ts)
{
	double left;
	left = Primary(ts);
	if (ts.eof()) return left;
	Token t = get_token(ts);
	while (true)
	{
		if (ts.eof()) {
			put_back(ts);
			return left;
		}
		switch (t.ctg) {
		case '*':
			left *= Primary(ts);
			if (ts.eof()) return left;
			t = get_token(ts);
			break;
		case '/': {
			//guarantee the right oprand is not 0
			double right = Primary(ts);
			if (abs(right) < 10e-6) throw runtime_error("Divided by 0");
			left /= right;
			if (ts.eof()) return left;
			t = get_token(ts);
			break;
		}
		case '%': {
			long int int_left = static_cast<int>(left);
			if (abs(int_left - left) > 10e-6) throw runtime_error("oprands is not an integer");
			double temp = Primary(ts);
			if (abs(temp) < 10e-6) throw runtime_error("Mod by 0");
			if (abs(temp - static_cast<int>(temp)) > 10e-6)
				throw runtime_error("operand is not an integer");
			if (temp < 0) throw runtime_error("operand is negetive");
			int_left %= static_cast<int>(temp);
			left = int_left;
			if (ts.eof()) return left;
			t = get_token(ts);
			break;
		}
		default:
			put_back(ts);
			return left;
		}
	}
}

double Primary(TokenStream &ts)
{
	Token t = get_token(ts);
	double left;
	switch (t.ctg) {
		//if token is a number
	case '8':
		left = t.value;
		if (ts.eof()) return left;
		//whether factorial exists, if more than one '!', do all the factorial.
		t = get_token(ts);
		while (t.ctg == '!') {
			left = fac(left);
			if (ts.eof()) return left;
			t = get_token(ts);
		}
		if (t.ctg != '!') put_back(ts);
		return left;
		//if token is a '(', then evaluate the expression in the bracket.
	case '(':
		left = Expression(ts);
		//get the ')'
		if (ts.eof()) throw runtime_error(") missing");
		t = get_token(ts);
		if (t.ctg != ')')
			throw runtime_error(") missing");
		if (ts.eof()) return left;
		//whether factorial exists, if more than one '!', do all the factorial.
		t = get_token(ts);
		while (t.ctg == '!') {
			left = fac(left);
			if (ts.eof()) return left;
			t = get_token(ts);
		}
		if (t.ctg != '!') put_back(ts);
		return left;
		//if a series of + is detected
	case '+':
		left = Primary(ts);
		return left;
		//if a series of - is detected
	case '-':
		left = -Primary(ts);
		return left;
	case 's':
		left = Primary(ts);
		if (left < 0) throw runtime_error("sqrt must be positive");
		left = sqrt(left);
		return left;
	default:
		// some unidentified use.
		throw runtime_error("Unkown identifier");
	}
}
#endif GRAMMER_H