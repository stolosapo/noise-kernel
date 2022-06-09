#include "MainTestSuite.h"
#include "argument/ArgumentParserTest.h"

MainTestSuite::MainTestSuite(): UnitTestSuite("Main Test Suite", 0)
{

}

MainTestSuite::~MainTestSuite()
{

}

void MainTestSuite::registerTests()
{
    registerTest(new ArgumentParserTest);
}
