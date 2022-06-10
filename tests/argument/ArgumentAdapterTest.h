#ifndef ArgumentAdapterTest_h__
#define ArgumentAdapterTest_h__

#include <noisetest/UnitTestSuite.h>

void test_argument_adapter_should_return_correct();
void test_argument_adapter_should_return_help();

class ArgumentAdapterTest: public NoiseTest::UnitTestSuite
{
protected:
	virtual void registerTests();

public:
	ArgumentAdapterTest();
	virtual ~ArgumentAdapterTest();

};

#endif // ArgumentAdapterTest_h__
