#include <iostream>
#include <signal.h>

#include <noisekernel/Argument.h>
#include <noisekernel/Signal.h>
#include <noisekernel/Observer.h>
#include <noisekernel/Thread.h>

#include "mocks/mocks.h"

using namespace std;

void argument_example(int argc, char* argv[]);
void signal_example();
void observer_example();
void thread_example();

int main(int argc, char* argv[])
{
    cout << "Example noisekernel" << endl << endl;

    argument_example(argc, argv);
    signal_example();
    observer_example();
    thread_example();
}

void argument_example(int argc, char* argv[])
{
    cout << "Example for arguments of noisekernel" << endl << endl;

    // First we create an new provider
    NoiseKernel::ArgumentProvider provider(argc, argv);

    // Then a new instance of the adapter that we have create for the specific system
    MockArgumentAdapter adapter(&provider);

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
    MockObserverSender aSender;
    cout << "Now sender has: " << aSender.counter << endl;

    // First we declate an Event
    NoiseKernel::Event onSomethingHappen;

    // and we add to it methods to run.. we can add more than one like delegate mode
    onSomethingHappen += mockObserverDelegate;

    // or as handlers if we want more complex things to do
    MockEventHandler aHandler;
    onSomethingHappen.addEventHandler(&aHandler);

    // when this event triggered (like this, with some args)
    NoiseKernel::EventArgs someArgs;
    onSomethingHappen.raise(&aSender, &someArgs);

    // Then happens whatever `mockDelegete` and `aHandler` says..
    cout << "Now sender has: " << aSender.counter << endl << endl;
}

void thread_example()
{
    cout << "Example for threads usage of noisekernel" << endl << endl;

    // First we create a new instance of Thread
    NoiseKernel::Thread th;

    // we assign to it a job to do, for example a mock one
    th += &mockThreadDelegate;

    // and start it with some input
    th.start(&th);
    // dont forget to wait in order for the thread to join back into system
    th.wait();
    cout << "thread finised!" << endl << endl;

    // Or use a Thread Pool
    NoiseKernel::ThreadPool pool(3);
    NoiseKernel::Thread *next = pool.getNext();
    next->attachDelegate(&mockThreadDelegate);
    next->start(next);
    next->wait();
    cout << "thread finised!" << endl << endl;
    pool.putBack(next);

    // Or use a TaskRunner
    NoiseKernel::TaskRunner runner;
    runner.registerTask("command1", &mockTaskDelegate);
    runner.registerTask("command_with_args", &mockTaskDelegate);

    runner.runTask("command1", NULL);
    runner.runTask("command_with_args?arg1=aa&arg2=lll&arg3=111", NULL);

    NoiseKernel::Task *task = runner.startTask("command_with_args?arg1=aa&arg2=lll&arg3=111", NULL);
    task->getRunningThread()->wait();

    // Dont forget to dispose
    delete task->getRunningThread();
    delete task;

    cout << "task finised!" << endl << endl;

}