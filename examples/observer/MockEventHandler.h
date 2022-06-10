#ifndef MockEventHandler_h__
#define MockEventHandler_h__

#include <noisekernel/Observer.h>

class MockEventHandler : public NoiseKernel::EventHandler
{
public:
    MockEventHandler();
    virtual ~MockEventHandler();

    virtual void onEvent(void* sender, NoiseKernel::EventArgs* e);
};

#endif // MockEventHandler_h__
