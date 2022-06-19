#ifndef BasicLogger_h__
#define BasicLogger_h__

#include <string>

using namespace std;

namespace NoiseKernel
{
    void fatal(string message);
    void error(string message);
    void warn(string message);
    void info(string message);
    void debug(string message);
    void trace(string message);
}

#endif // BasicLogger_h__
