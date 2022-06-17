#ifndef Signal_h__
#define Signal_h__

#include <vector>
#include <map>
#include <string>
#include <signal.h>

using namespace std;

namespace NoiseKernel
{
    volatile static sig_atomic_t sigint_signaled;

    typedef void (*SignalHandlerFunction)(int);

    class Signal
    {
    private:
        int signalNumber;
        SignalHandlerFunction handler;

    public:
        Signal(int signalNumber, SignalHandlerFunction handler);
        virtual ~Signal();

        virtual int getSignalNumber();

        virtual void setup();
        virtual void raiseSignal();

        virtual sig_atomic_t getSignaled() = 0;
        virtual void reset() = 0;
    };

    class Signal_SIGINT : public Signal
    {
    private:
        static void signal_handler(int sig);

    public:
        Signal_SIGINT();
        Signal_SIGINT(SignalHandlerFunction external_handler);
        virtual ~Signal_SIGINT();

        virtual sig_atomic_t getSignaled();
        virtual void reset();
    };

    class SignalHandler
    {
    private:
        map<int, Signal*> signals;

    protected:
        void registerSignal(Signal* sig);

    public:
        SignalHandler();
        virtual ~SignalHandler();

        void setup();
        void reset(int sig);
        int signaled(int sig);

        virtual void registerSignals() = 0;
    };

    class SignalAdapter: public SignalHandler
    {
    public:
        SignalAdapter();
        virtual ~SignalAdapter();

        virtual void registerSignals();

        bool gotSigInt();
        bool gotSigIntAndReset();
    };

}

#endif // Signal_h__
