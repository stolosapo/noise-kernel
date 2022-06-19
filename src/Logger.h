#ifndef Logger_h__
#define Logger_h__

#include <string>

using namespace std;

namespace NoiseKernel
{
    typedef void (*LogDelegate)(string message);

    struct LogService
    {
        LogDelegate fatal;
        LogDelegate error;
        LogDelegate warn;
        LogDelegate info;
        LogDelegate debug;
        LogDelegate trace;
    };

    LogService buildBasicLogService();
}

#endif // Logger_h__
