#include "../Thread.h"
#include "../utils/StringHelper.h"

using namespace NoiseKernel;

const string TaskRunner::TASK_DELIMITER = "?";
const string TaskRunner::PARAM_DELIMITER = "&";

TaskRunner::TaskRunner()
{
    tasks = new ValueStrategy<string, ThreadDelegate>;
}

TaskRunner::~TaskRunner()
{
    if (tasks != NULL)
    {
        delete tasks;
    }
}

string TaskRunner::getTaskFromParametrizedCommand(string command)
{
    vector<string> params = split(command, TASK_DELIMITER);

    if (params.size() < 1)
    {
        return "";
    }

    return params.at(0);
}

vector<string> TaskRunner::getParamsFromParametrizedCommand(string command)
{
    vector<string> params = split(command, TASK_DELIMITER);

    if (params.size() < 2)
    {
        return vector<string>();
    }

    string paramsStr = params.at(1);

    return split(paramsStr, PARAM_DELIMITER);
}

void TaskRunner::registerTask(string taskName, ThreadDelegate delegate)
{
    tasks->registerStrategy(taskName, delegate);
}

bool TaskRunner::taskExist(string taskName)
{
    return tasks->keyExists(taskName);
}

bool TaskRunner::parametrizedTaskExist(string taskName)
{
    return taskExist(getTaskFromParametrizedCommand(taskName));
}

// TODO: For Future needs..
// Task* TaskRunner::startTask(string fullTaskName, void* data)
// {
//     string taskName = getTaskFromParametrizedCommand(fullTaskName);
//     vector<string> params = getParamsFromParametrizedCommand(taskName);

//     ThreadDelegate delegate = tasks->get(taskName);

//     if (delegate == NULL)
//     {
//         return NULL;
//     }

//     Thread *runningThread = new Thread;
//     runningThread->attachDelegate(delegate);

//     Task* task = new Task(taskName, params, runningThread, data);
//     runningThread->start(task);

//     return task;
// }

// Task* TaskRunner::startTask(ThreadDelegate delegate, void* data)
// {
//     Thread *runningThread = new Thread;
//     runningThread->attachDelegate(delegate);

//     vector<string> params;

//     Task* task = new Task("", params, runningThread, data);
//     runningThread->start(task);

//     return task;
// }

void* TaskRunner::runTask(string fullTaskName, void* data)
{
    string taskName = getTaskFromParametrizedCommand(fullTaskName);
    vector<string> params = getParamsFromParametrizedCommand(taskName);

    ThreadDelegate delegate = tasks->get(taskName);

    if (delegate == NULL)
    {
        return NULL;
    }

    Task* context = new Task(taskName, params, NULL, data);
    void* result = NULL;

    try
    {
        result = delegate(context);
    }
    catch(exception& e)
    {
        delete context;
        throw e;
    }

    delete context;

    return result;
}
