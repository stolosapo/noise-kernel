#include <iostream>
#include <signal.h>

#include <noisekernel/Argument.h>
#include <noisekernel/Signal.h>
#include <noisekernel/Observer.h>

#include "argument/ExampleArgumentAdapter.h"
#include "observer/MockDelegate.h"
#include "observer/MockEventHandler.h"
#include "observer/MockSender.h"

using namespace std;

int argument_example(int argc, char* argv[]);
void signal_example();
void observer_example();

int main(int argc, char* argv[])
{
    cout << "Example noisekernel" << endl << endl;

    argument_example(argc, argv);
    signal_example();
    observer_example();
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
}

void observer_example()
{
    cout << "Example for observers usage of noisekernel" << endl << endl;

    // We need a sender that probably will trigger the event
    MockSender aSender;
    cout << "Now sender has: " << aSender.counter << endl;

    // First we declate an Event
    NoiseKernel::Event onSomethingHappen;

    // and we add to it methods to run.. we can add more than one like delegate mode
    onSomethingHappen += mockDelegate;

    // or as handlers if we want more complex things to do
    MockEventHandler aHandler;
    onSomethingHappen.addEventHandler(&aHandler);

    // when this event triggered (like this, with some args)
    NoiseKernel::EventArgs someArgs;
    onSomethingHappen.raise(&aSender, &someArgs);

    // Then happens whatever `mockDelegete` and `aHandler` says..
    cout << "Now sender has: " << aSender.counter << endl << endl;
}
