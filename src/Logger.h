#ifndef Logger_h__
#define Logger_h__

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
}

#endif // Logger_h__
