#ifndef ArgumentParserTest_h__
#define ArgumentParserTest_h__

#include <noisetest/UnitTestSuite.h>

void test_arg_parser();
void test_arg_parser_with_no_args();

class ArgumentParserTest: public NoiseTest::UnitTestSuite
{
protected:
	virtual void registerTests();

public:
	ArgumentParserTest();
	virtual ~ArgumentParserTest();

};

#endif // ArgumentParserTest_h__
