#pragma once
#ifndef DIYFUNCTION_H
#define DIYFUNCTION_H

#include <stdexcept>
#include <string>
#include <math.h>
#include "Function.h"
using std::string;
using std::runtime_error;

string extract(string rawstr, string::size_type beg, string::size_type en);
long int fac(double i);

string extract(string rawstr, string::size_type beg, string::size_type en)
{
	string prodt = "";
	for (string::size_type st = beg; st != en; ++st) {
		prodt += rawstr[st];
	}
	return prodt;
}

long int fac(double i)
{
	long f(1);
	if (i < 0) throw runtime_error("Negetive!.");
	if (abs(i - static_cast<int>(i))>10e-6) throw runtime_error("factorial must be integer");
	if (i == 0) return 1;
	for (int j = 1; j <= i; ++j)
		f *= j;
	return f;
}

#endif DIYFUNCTION_H