#include "MockEventHandler.h"
#include "MockSender.h"

MockEventHandler::MockEventHandler() : EventHandler()
{

}

MockEventHandler::~MockEventHandler()
{

}

void MockEventHandler::onEvent(void* sender, NoiseKernel::EventArgs* e)
{
    MockSender* mockSender = (MockSender*) sender;
    mockSender->counter++;
}
