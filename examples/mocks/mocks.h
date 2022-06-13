#ifndef mocks_h__
#define mocks_h__

#include <iostream>
#include <string>
#include <noisekernel/Argument.h>
#include <noisekernel/Observer.h>
#include <noisekernel/Thread.h>

using namespace std;

void mockObserverDelegate(void* sender, NoiseKernel::EventArgs* e);
void* mockThreadDelegate(void* data);
void* mockTaskWithContextDelegate(void* data);

class MockArgumentAdapter: public NoiseKernel::ArgumentAdapter
{
protected:
    virtual string title();

public:
	MockArgumentAdapter(NoiseKernel::ArgumentProvider* provider);
    virtual ~MockArgumentAdapter();

    virtual void registerArguments();

    string getName();
    string getDescription();
    int getANumber();
};

class MockObserverSender
{
public:
    int counter;

    MockObserverSender();
    virtual ~MockObserverSender();

    void test();
};

class MockEventHandler : public NoiseKernel::EventHandler
{
public:
    MockEventHandler();
    virtual ~MockEventHandler();

    virtual void onEvent(void* sender, NoiseKernel::EventArgs* e);
};

#endif // mocks_h__
