#ifndef ExampleArgumentAdapter_h__
#define ExampleArgumentAdapter_h__

#include <string>
#include <noisekernel/Argument.h>

using namespace std;

class ExampleArgumentAdapter: public NoiseKernel::ArgumentAdapter
{
protected:
    virtual string title();

public:
	ExampleArgumentAdapter(NoiseKernel::ArgumentProvider* provider);
    virtual ~ExampleArgumentAdapter();

    virtual void registerArguments();

    string getName();
    string getDescription();
    int getANumber();
};

#endif // ExampleArgumentAdapter_h__
