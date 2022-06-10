#include "MockDelegate.h"
#include "MockSender.h"

void mockDelegate(void* sender, NoiseKernel::EventArgs* e)
{
    MockSender* mockSender = (MockSender*) sender;
    mockSender->counter++;
}
