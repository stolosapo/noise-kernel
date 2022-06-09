#include "ArgumentProviderTest.h"
#include "../../src/Argument.h"
#include <noisetest/Assertion.h>

using namespace NoiseTest;
using namespace NoiseKernel;

ArgumentProviderTest::ArgumentProviderTest(): UnitTestSuite("Argument Provider Test Suite", 0)
{

}

ArgumentProviderTest::~ArgumentProviderTest()
{

}

void ArgumentProviderTest::registerTests()
{
    registerTest("Should return correct if has argument", &test_argument_provider_should_return_correct_if_has_argument);
    registerTest("Should return correct if has not argument", &test_argument_provider_should_return_correct_if_has_not_argument);
    registerTest("Should return correct value as string", &test_argument_provider_should_return_correct_value_as_string);
    registerTest("Should return correct value as string if not string", &test_argument_provider_should_return_correct_value_as_string_if_not_string);
    registerTest("Should return correct value as int", &test_argument_provider_should_return_correct_value_as_int);
    registerTest("Should return correct value as int if not int", &test_argument_provider_should_return_correct_value_as_int_if_not_int);
    registerTest("Should return correct value as bool", &test_argument_provider_should_return_correct_value_as_bool);
    registerTest("Should return correct value as bool if not bool", &test_argument_provider_should_return_correct_value_as_bool_if_not_bool);
}

void test_argument_provider_should_return_correct_if_has_argument()
{
    const int SIZE = 3;
    int argc = SIZE;
    char* argv[SIZE];

    argv[0] = (char*) "./executable";
    argv[1] = (char*) "--arg1";
    argv[2] = (char*) "val1";

    ArgumentProvider provider(argc, argv);

    assertTrue(provider.hasArg("arg1"));
}

void test_argument_provider_should_return_correct_if_has_not_argument()
{
    const int SIZE = 3;
    int argc = SIZE;
    char* argv[SIZE];

    argv[0] = (char*) "./executable";
    argv[1] = (char*) "--arg1";
    argv[2] = (char*) "val1";

    ArgumentProvider provider(argc, argv);

    assertFalse(provider.hasArg("arg2"));
}

void test_argument_provider_should_return_correct_value_as_string()
{
    const int SIZE = 3;
    int argc = SIZE;
    char* argv[SIZE];

    argv[0] = (char*) "./executable";
    argv[1] = (char*) "--arg1";
    argv[2] = (char*) "val1";

    ArgumentProvider provider(argc, argv);

    assertEqual("val1", provider.getStringValue("arg1"));
}

void test_argument_provider_should_return_correct_value_as_string_if_not_string()
{
    const int SIZE = 3;
    int argc = SIZE;
    char* argv[SIZE];

    argv[0] = (char*) "./executable";
    argv[1] = (char*) "--arg1";
    argv[2] = (char*) "120";

    ArgumentProvider provider(argc, argv);

    assertEqual("120", provider.getStringValue("arg1"));
}

void test_argument_provider_should_return_correct_value_as_int()
{
    const int SIZE = 3;
    int argc = SIZE;
    char* argv[SIZE];

    argv[0] = (char*) "./executable";
    argv[1] = (char*) "--arg1";
    argv[2] = (char*) "120";

    ArgumentProvider provider(argc, argv);

    assertEqual(120, provider.getIntValue("arg1"));
}

void test_argument_provider_should_return_correct_value_as_int_if_not_int()
{
    const int SIZE = 3;
    int argc = SIZE;
    char* argv[SIZE];

    argv[0] = (char*) "./executable";
    argv[1] = (char*) "--arg1";
    argv[2] = (char*) "asdasd";

    ArgumentProvider provider(argc, argv);

    assertEqual(0, provider.getIntValue("arg1"));
}

void test_argument_provider_should_return_correct_value_as_bool()
{
    const int SIZE = 3;
    int argc = SIZE;
    char* argv[SIZE];

    argv[0] = (char*) "./executable";
    argv[1] = (char*) "--arg1";
    argv[2] = (char*) "true";

    ArgumentProvider provider(argc, argv);

    assertTrue(provider.getBoolValue("arg1"));
}

void test_argument_provider_should_return_correct_value_as_bool_if_not_bool()
{
    const int SIZE = 3;
    int argc = SIZE;
    char* argv[SIZE];

    argv[0] = (char*) "./executable";
    argv[1] = (char*) "--arg1";
    argv[2] = (char*) "adasd";

    ArgumentProvider provider(argc, argv);

    assertFalse(provider.getBoolValue("arg1"));
}
