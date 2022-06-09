#include "ArgumentParserTest.h"
#include "../../src/Argument.h"
#include <noisetest/Assertion.h>

using namespace NoiseTest;
using namespace NoiseKernel;

ArgumentParserTest::ArgumentParserTest(): UnitTestSuite("Argument Parser Test Suite", 0)
{

}

ArgumentParserTest::~ArgumentParserTest()
{

}

void ArgumentParserTest::registerTests()
{
	registerTest("Should parse arguments correctly", &test_arg_parser);
}

void test_arg_parser()
{
	const int SIZE = 8;
	int argc = SIZE;
	char* argv[SIZE];

	argv[0] = (char*) "./executable";
	argv[1] = (char*) "--arg1";
	argv[2] = (char*) "val1";
	argv[3] = (char*) "--arg2";
	argv[4] = (char*) "val2";
	argv[5] = (char*) "--arg3";
    argv[6] = (char*) "--arg4";
    argv[7] = (char*) "val4";

	ArgumentParser parser;
	ArgumentList results = parser.parse(argc, argv);

	assertEqual("val1", results.get("arg1"));
	assertEqual("val2", results.get("arg2"));
	assertEqual("", results.get("arg3"));
	assertEqual("val4", results.get("arg4"));
}
