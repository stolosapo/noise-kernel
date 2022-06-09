#ifndef ArgumentParserTest_h__
#define ArgumentParserTest_h__

#include <noisetest/UnitTestSuite.h>

void test_arg_parser();

class ArgumentParserTest: public NoiseTest::UnitTestSuite
{
protected:
	virtual void registerTests();

public:
	ArgumentParserTest();
	virtual ~ArgumentParserTest();

};

#endif // ArgumentParserTest_h__
