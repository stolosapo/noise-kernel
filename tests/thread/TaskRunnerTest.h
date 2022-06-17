#ifndef TaskRunnerTest_h__
#define TaskRunnerTest_h__

#include <noisetest/UnitTestSuite.h>

void test_task_runner_task_exist();
void test_task_runner_task_not_exist();
void test_task_runner_task_run_task_success();
void test_task_runner_task_run_task_failed();

class TaskRunnerTest: public NoiseTest::UnitTestSuite
{
protected:
	virtual void registerTests();

public:
	TaskRunnerTest();
	virtual ~TaskRunnerTest();

};

#endif // TaskRunnerTest_h__
