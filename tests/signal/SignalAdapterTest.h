#ifndef SignalAdapterTest_h__
#define SignalAdapterTest_h__

#include <noisetest/UnitTestSuite.h>

void test_signal_adapter_should_return_correct_if_got_sigint();
void test_signal_adapter_should_return_correct_if_got_sigint_and_reset();

class SignalAdapterTest: public NoiseTest::UnitTestSuite
{
protected:
	virtual void registerTests();

public:
	SignalAdapterTest();
	virtual ~SignalAdapterTest();

};

#endif // SignalAdapterTest_h__
