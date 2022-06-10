#include "SignalAdapterTest.h"
#include "../../src/Signal.h"
#include <noisetest/Assertion.h>

using namespace NoiseTest;
using namespace NoiseKernel;

SignalAdapterTest::SignalAdapterTest(): UnitTestSuite("Signal Adapter Test Suite", 0)
{

}

SignalAdapterTest::~SignalAdapterTest()
{

}

void SignalAdapterTest::registerTests()
{
    registerTest("Should return correct if got sigint", &test_signal_adapter_should_return_correct_if_got_sigint);
    registerTest("Should return correct if got sigint and reset", &test_signal_adapter_should_return_correct_if_got_sigint_and_reset);
}

void test_signal_adapter_should_return_correct_if_got_sigint()
{
    SignalAdapter adapter;
    adapter.registerSignals();
    adapter.setup();

    raise(SIGINT);
    assertTrue(adapter.gotSigInt());
    assertTrue(adapter.gotSigInt());
}

void test_signal_adapter_should_return_correct_if_got_sigint_and_reset()
{
    SignalAdapter adapter;
    adapter.registerSignals();
    adapter.setup();

    raise(SIGINT);
    assertTrue(adapter.gotSigIntAndReset());
    assertFalse(adapter.gotSigInt());
}

