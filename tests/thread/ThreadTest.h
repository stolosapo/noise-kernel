#ifndef ThreadTest_h__
#define ThreadTest_h__

#include <noisetest/UnitTestSuite.h>

void test_thread_start_with_wait();

class ThreadTest: public NoiseTest::UnitTestSuite
{
protected:
	virtual void registerTests();

public:
	ThreadTest();
	virtual ~ThreadTest();

};

#endif // ThreadTest_h__
