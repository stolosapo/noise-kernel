#include "../Logger.h"
#include "BasicLogger.h"
#include <iostream>
#include <time.h>

using namespace std;
using namespace NoiseKernel;

LogService NoiseKernel::buildBasicLogService()
{
    LogService logger;
    
    logger.fatal = &fatal;
    logger.error = &error;
    logger.warn = &warn;
    logger.info = &info;
    logger.debug = &debug;
    logger.trace = &trace;

    return logger;
}

void NoiseKernel::fatal(string message)
{
    cout << "[FATAL] " << time(0) << " " << message << endl;
}

void NoiseKernel::error(string message)
{
    cout << "[ERROR] "  << time(0) << " " << message << endl;
}

void NoiseKernel::warn(string message)
{
    cout << "[WARN] "  << time(0) << " " << message << endl;
}

void NoiseKernel::info(string message)
{
    cout << "[INFO] "  << time(0) << " " << message << endl;
}

void NoiseKernel::debug(string message)
{
    cout << "[DEBUG] "  << time(0) << " " << message << endl;
}

void NoiseKernel::trace(string message)
{
    cout << "[TRACE] "  << time(0) << " " << message << endl;
}
