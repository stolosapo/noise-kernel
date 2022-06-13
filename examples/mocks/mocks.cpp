#include "mocks.h"


MockObserverSender::MockObserverSender()
{
    counter = 0;
}

MockObserverSender::~MockObserverSender()
{

}

void MockObserverSender::test()
{

}

MockEventHandler::MockEventHandler() : EventHandler()
{

}

MockEventHandler::~MockEventHandler()
{

}

void MockEventHandler::onEvent(void* sender, NoiseKernel::EventArgs* e)
{
    MockObserverSender* mockSender = (MockObserverSender*) sender;
    mockSender->counter++;
}

MockArgumentAdapter::MockArgumentAdapter(NoiseKernel::ArgumentProvider* provider): NoiseKernel::ArgumentAdapter(provider)
{

}

MockArgumentAdapter::~MockArgumentAdapter()
{

}

string MockArgumentAdapter::title()
{
    return "Example for Arguments of NoiseKernel";
}

void MockArgumentAdapter::registerArguments()
{
    registerArg("name", "The Name of the example");
    registerArg("description", "The Description");
    registerArg("number", "The Number");
}

string MockArgumentAdapter::getName()
{
    return getStringValue("name");
}

string MockArgumentAdapter::getDescription()
{
    return getStringValue("description");
}

int MockArgumentAdapter::getANumber()
{
    return getIntValue("number");
}

void mockObserverDelegate(void* sender, NoiseKernel::EventArgs* e)
{
    MockObserverSender* mockSender = (MockObserverSender*) sender;
    mockSender->counter++;
}

void* mockThreadDelegate(void* data)
{
    if (data == NULL)
    {
        cout << "*** This a task is running in a thread but with out data passed.." << endl;
        return NULL;
    }
    
    NoiseKernel::Thread *th = (NoiseKernel::Thread*) data;

    cout << "*** This a task is running in thread: id->" 
        << th->getId() 
        << " poolIndex->" << th->getPoolIndex() << endl;
    
    return NULL;
}

void* mockTaskWithContextDelegate(void* data)
{
    NoiseKernel::TaskContext *context = (NoiseKernel::TaskContext*) data;

    cout << "*** Running task: " << context->getTask() 
        << " param0: " << context->getParam(0) 
        << " param1: " << context->getParam(1) 
        << " param2: " << context->getParam(2) << endl;
    
    return NULL;
}