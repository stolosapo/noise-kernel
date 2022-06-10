#ifndef StringHelper_h__
#define StringHelper_h__

#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>

using namespace std;

namespace NoiseKernel
{
    template <typename T>
    T stringToNumber(const string &str);
    string pad(const string& str, int times);

    template <typename T>
    T stringToNumber(const string &str)
    {
        istringstream ss(str);
        T result;
        return ss >> result ? result : 0;
    }
}

#endif /* StringHelper_h__ */
