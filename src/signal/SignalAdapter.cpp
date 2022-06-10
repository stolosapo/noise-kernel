#include "../Signal.h"

using namespace NoiseKernel;

SignalAdapter::SignalAdapter() : SignalHandler()
{

}

SignalAdapter::~SignalAdapter()
{

}

void SignalAdapter::registerSignals()
{
    registerSignal(new Signal_SIGINT);
}

bool SignalAdapter::gotSigInt()
{
    return signaled(SIGINT);
}

bool SignalAdapter::gotSigIntAndReset()
{
    bool got = gotSigInt();

    if (got)
    {
        reset(SIGINT);
    }


    return got;
}
