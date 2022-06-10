#include <iostream>
#include "Argument.h"
#include "Signal.h"
#include "argument/MockAdapter.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "noisekernel Library" << endl << endl;

    NoiseKernel::ArgumentProvider provider(argc, argv);
    MockAdapter adapter(&provider);
    adapter.registerArguments();
    cout << adapter.help() << endl;

    // NoiseKernel::SignalAdapter signalAdapter;
    // signalAdapter.registerSignals();
    // signalAdapter.setup();
    // cout << "Got SIGINT: " << signalAdapter.gotSigInt() << endl;
    // raise(SIGINT);
    // cout << "Got SIGINT and reset it: " << signalAdapter.gotSigIntAndReset() << endl;

    cout << "Bye Bye.." << endl;
}
