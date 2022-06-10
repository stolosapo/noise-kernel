#include "ArgumentAdapterTest.h"
#include "../../src/Argument.h"
#include "../../src/argument/MockAdapter.h"
#include <noisetest/Assertion.h>

using namespace NoiseTest;
using namespace NoiseKernel;

ArgumentAdapterTest::ArgumentAdapterTest(): UnitTestSuite("Argument Adapter Test Suite", 0)
{

}

ArgumentAdapterTest::~ArgumentAdapterTest()
{

}

void ArgumentAdapterTest::registerTests()
{
    registerTest("Should return correct arguments", &test_argument_adapter_should_return_correct);
    registerTest("Should return correct help", &test_argument_adapter_should_return_help);
}

void test_argument_adapter_should_return_correct()
{
    const int SIZE = 7;
    int argc = SIZE;
    char* argv[SIZE];

    argv[0] = (char*) "./executable";
    argv[1] = (char*) "--arg1";
    argv[2] = (char*) "val1";
    argv[3] = (char*) "--arg2";
    argv[4] = (char*) "12";
    argv[5] = (char*) "--arg3";
    argv[6] = (char*) "true";

    ArgumentProvider provider(argc, argv);
    MockAdapter adapter(&provider);

    assertEqual("val1", adapter.getArg1());
    assertEqual(12, adapter.getArg2());
    assertEqual(true, adapter.getArg3());
}

void test_argument_adapter_should_return_help()
{
    const int SIZE = 0;
    int argc = SIZE;
    char* argv[SIZE];

    ArgumentProvider provider(argc, argv);
    MockAdapter adapter(&provider);
    adapter.registerArguments();

    string help = adapter.help();

    cout << help << endl;
}
