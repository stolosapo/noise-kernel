#ifndef MockAdapter_h__
#define MockAdapter_h__

#include <string>
#include "../Argument.h"

using namespace std;

class MockAdapter: public NoiseKernel::ArgumentAdapter
{
protected:
    virtual string title();

public:
	MockAdapter(NoiseKernel::ArgumentProvider* provider);
    virtual ~MockAdapter();

    virtual void registerArguments();

    string getArg1();
    int getArg2();
    bool getArg3();
};

#endif // MockAdapter_h__
