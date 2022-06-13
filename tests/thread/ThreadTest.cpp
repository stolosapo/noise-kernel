#include "ThreadTest.h"
#include "../../src/Thread.h"
#include <noisetest/Assertion.h>

using namespace NoiseTest;
using namespace NoiseKernel;

ThreadTest::ThreadTest(): UnitTestSuite("Thread Test Suite", 0)
{

}

ThreadTest::~ThreadTest()
{

}

void ThreadTest::registerTests()
{
    registerTest("Should start and wait to finished", &test_thread_start_with_wait);
}

void* mockDelegate(void* data)
{
    ((int*)data)[0] = 1;
    return NULL;
}

void test_thread_start_with_wait()
{
    int* ii = new int[1];

    Thread th;

    th += &mockDelegate;
    th.start(ii);
    th.wait();

    assertEqual(ii[0], 1);
}
