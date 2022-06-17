#ifndef ThreadPoolTest_h__
#define ThreadPoolTest_h__

#include <noisetest/UnitTestSuite.h>

void test_thread_pool_has_next();
void test_thread_pool_reach_size();
void test_thread_pool_get_next();
void test_thread_pool_get_next_use_queue_pop();
void test_thread_pool_put_back();
void test_thread_pool_multi_threading();

class ThreadPoolTest: public NoiseTest::UnitTestSuite
{
protected:
	virtual void registerTests();

public:
	ThreadPoolTest();
	virtual ~ThreadPoolTest();

};

#endif // ThreadPoolTest_h__
