#ifndef ArgumentProviderTest_h__
#define ArgumentProviderTest_h__

#include <noisetest/UnitTestSuite.h>

void test_argument_provider_should_return_correct_if_has_argument();
void test_argument_provider_should_return_correct_if_has_not_argument();
void test_argument_provider_should_return_correct_value_as_string();
void test_argument_provider_should_return_correct_value_as_string_if_not_string();
void test_argument_provider_should_return_correct_value_as_int();
void test_argument_provider_should_return_correct_value_as_int_if_not_int();
void test_argument_provider_should_return_correct_value_as_bool();
void test_argument_provider_should_return_correct_value_as_bool_if_not_bool();

class ArgumentProviderTest: public NoiseTest::UnitTestSuite
{
protected:
	virtual void registerTests();

public:
	ArgumentProviderTest();
	virtual ~ArgumentProviderTest();

};

#endif // ArgumentProviderTest_h__
