#include "TaskRunnerTest.h"
#include "../../src/Thread.h"
#include <noisetest/Assertion.h>

using namespace NoiseTest;
using namespace NoiseKernel;

TaskRunnerTest::TaskRunnerTest(): UnitTestSuite("Task Runner Test Suite", 0)
{

}

TaskRunnerTest::~TaskRunnerTest()
{

}

void TaskRunnerTest::registerTests()
{
    registerTest("Should task exist", &test_task_runner_task_exist);
    registerTest("Should task not exist", &test_task_runner_task_not_exist);
    registerTest("Should task run task success", &test_task_runner_task_run_task_success);
    registerTest("Should task run task failed", &test_task_runner_task_run_task_failed);
}

void* a_task_to_do(void* task)
{
    return ((NoiseKernel::Task*) task)->getData();
}

void test_task_runner_task_exist()
{
    NoiseKernel::TaskRunner runner;
    runner.registerTask("a_task", &a_task_to_do);

    assertTrue(runner.taskExist("a_task"));
    assertTrue(runner.taskExist("a_task?p1=v1&p2=v2"));
}

void test_task_runner_task_not_exist()
{
    NoiseKernel::TaskRunner runner;
    runner.registerTask("a_task", &a_task_to_do);

    assertFalse(runner.taskExist("a_not_task"));
}

void test_task_runner_task_run_task_success()
{
    NoiseKernel::TaskRunner runner;
    runner.registerTask("a_task", &a_task_to_do);

    int* param = new int(5);
    int* results = (int*) runner.runTask("a_task", param);

    bool equal = results == param;

    assertTrue(equal);
}

void test_task_runner_task_run_task_failed()
{
    NoiseKernel::TaskRunner runner;
    runner.registerTask("a_task", &a_task_to_do);

    int* param = new int;
    void* results = runner.runTask("a_task_not", param);

    bool isNull = results == NULL;

    assertTrue(isNull);
}
