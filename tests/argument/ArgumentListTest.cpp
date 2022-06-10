#include "ArgumentListTest.h"
#include "../../src/Argument.h"
#include <noisetest/Assertion.h>

using namespace NoiseTest;
using namespace NoiseKernel;

ArgumentListTest::ArgumentListTest(): UnitTestSuite("Argument List Test Suite", 0)
{

}

ArgumentListTest::~ArgumentListTest()
{

}

void ArgumentListTest::registerTests()
{
    registerTest("Should return correct size", &test_argument_list_should_return_correct_size);
    registerTest("Should return correct if exists", &test_argument_list_should_return_correct_if_exists);
    registerTest("Should return correct if not exists", &test_argument_list_should_return_correct_if_not_exists);
    registerTest("Should return correct value if exists", &test_argument_list_should_return_correct_value_if_exists);
    registerTest("Should return correct value if not exists", &test_argument_list_should_return_correct_value_if_not_exists);
    registerTest("Should return correct when is empty", &test_argument_list_should_return_correct_when_is_empty);
}

void test_argument_list_should_return_correct_size()
{
    Argument a1("a1", "v1");
    Argument a2("a2", "v2");
    Argument a3("a3", "v3");

    vector<Argument> vector;
    vector.push_back(a1);
    vector.push_back(a2);
    vector.push_back(a3);

    ArgumentList list(vector);

    assertEqual(3, list.size());
}

void test_argument_list_should_return_correct_if_exists()
{
    Argument a1("a1", "v1");
    Argument a2("a2", "v2");
    Argument a3("a3", "v3");

    vector<Argument> vector;
    vector.push_back(a1);
    vector.push_back(a2);
    vector.push_back(a3);

    ArgumentList list(vector);

    assertTrue(list.exist("a1"));
    assertTrue(list.exist("a2"));
    assertTrue(list.exist("a3"));
}

void test_argument_list_should_return_correct_if_not_exists()
{
    Argument a1("a1", "v1");
    Argument a2("a2", "v2");
    Argument a3("a3", "v3");

    vector<Argument> vector;
    vector.push_back(a1);
    vector.push_back(a2);
    vector.push_back(a3);

    ArgumentList list(vector);

    assertFalse(list.exist("a5"));
}

void test_argument_list_should_return_correct_value_if_exists()
{
    Argument a1("a1", "v1");
    Argument a2("a2", "v2");
    Argument a3("a3", "v3");

    vector<Argument> vector;
    vector.push_back(a1);
    vector.push_back(a2);
    vector.push_back(a3);

    ArgumentList list(vector);

    assertEqual("v1", list.get("a1"));
    assertEqual("v2", list.get("a2"));
    assertEqual("v3", list.get("a3"));
}

void test_argument_list_should_return_correct_value_if_not_exists()
{
    Argument a1("a1", "v1");
    Argument a2("a2", "v2");
    Argument a3("a3", "v3");

    vector<Argument> vector;
    vector.push_back(a1);
    vector.push_back(a2);
    vector.push_back(a3);

    ArgumentList list(vector);

    assertEqual("", list.get("a5"));
}

void test_argument_list_should_return_correct_when_is_empty()
{
    vector<Argument> vector;
    ArgumentList list(vector);

    assertEqual("", list.get("a5"));
}
