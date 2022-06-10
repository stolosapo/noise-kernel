#include <iostream>
#include <noisekernel/Argument.h>
#include <noisekernel/Signal.h>
#include "argument/ExampleArgumentAdapter.h"
#include <unistd.h>
#include <signal.h>

using namespace std;

int argument_example(int argc, char* argv[]);
void signal_example();

int main(int argc, char* argv[])
{
    cout << "Example noisekernel" << endl << endl;

    argument_example(argc, argv);
    signal_example();
}

int argument_example(int argc, char* argv[])
{
    cout << "Example for arguments of noisekernel" << endl << endl;

    // First we create an new provider
    NoiseKernel::ArgumentProvider provider(argc, argv);

    // Then a new instance of the adapter that we have create for the specific system
    ExampleArgumentAdapter adapter(&provider);

    // not forget to register the arguments
    adapter.registerArguments();

    // and is ready for use
    cout << "Name: " << adapter.getName() << endl
        << "Description: " << adapter.getDescription() << endl
        << "Number: " << adapter.getANumber() << endl << endl
        << adapter.help() << endl;
}

void signal_example()
{
    cout << "Example for signal handling of noisekernel" << endl << endl;

    // We create a signal adapter
    NoiseKernel::SignalAdapter adapter;

    // not forget to register signals and setup
    // for now only sigint signal captured
    adapter.registerSignals();
    adapter.setup();

    cout << "SIGINT: " << adapter.gotSigInt() << endl;
    raise(SIGINT);
    cout << "SIGINT and reseting signal: " << adapter.gotSigIntAndReset() << endl;

    for (long long i = 0; i < 9223372036854775807; i++)
    {
        if (adapter.gotSigIntAndReset())
        {
            cout << "have to go.." << endl;
            break;
        }
    }
}
