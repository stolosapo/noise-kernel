#include <iostream>
#include <string>
#include <limits>
#include <stdio.h>

#include "Console.h"

using namespace std;
using namespace NoiseKernel;

string NoiseKernel::inLine()
{
	string s;
	getline(cin , s);
	return s;
}
