#ifndef ArgumentListTest_h__
#define ArgumentListTest_h__

#include <noisetest/UnitTestSuite.h>

void test_argument_list_should_return_correct_size();
void test_argument_list_should_return_correct_if_exists();
void test_argument_list_should_return_correct_if_not_exists();
void test_argument_list_should_return_correct_value_if_exists();
void test_argument_list_should_return_correct_value_if_not_exists();
void test_argument_list_should_return_correct_when_is_empty();

class ArgumentListTest: public NoiseTest::UnitTestSuite
{
protected:
	virtual void registerTests();

public:
	ArgumentListTest();
	virtual ~ArgumentListTest();

};

#endif // ArgumentListTest_h__
