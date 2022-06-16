#include "MainTestSuite.h"
#include "argument/ArgumentParserTest.h"
#include "argument/ArgumentListTest.h"
#include "argument/ArgumentProviderTest.h"
#include "argument/ArgumentAdapterTest.h"
#include "signal/SignalAdapterTest.h"
#include "observer/EventTest.h"
#include "thread/ThreadTest.h"
#include "thread/ThreadPoolTest.h"
#include "thread/TaskRunnerTest.h"

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
    registerTest(new ArgumentAdapterTest);
    registerTest(new SignalAdapterTest);
    registerTest(new EventTest);
    registerTest(new ThreadTest);
    registerTest(new ThreadPoolTest);
    registerTest(new TaskRunnerTest);
}
