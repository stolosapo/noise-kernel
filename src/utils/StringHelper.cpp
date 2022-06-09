#include "StringHelper.h"

string NoiseKernel::pad(const string& str, int times)
{
    string mess = "";

    for (int i = 0; i < times; i++)
    {
        mess += str;
    }

    return mess;
}
