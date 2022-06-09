#include "MainTestSuite.h"
#include "argument/ArgumentParserTest.h"
#include "argument/ArgumentListTest.h"
#include "argument/ArgumentProviderTest.h"

MainTestSuite::MainTestSuite(): UnitTestSuite("Main Test Suite", 0)
{

}

MainTestSuite::~MainTestSuite()
{

}

void MainTestSuite::registerTests()
{
    registerTest(new ArgumentListTest);
    registerTest(new ArgumentParserTest);
    registerTest(new ArgumentProviderTest);
}
