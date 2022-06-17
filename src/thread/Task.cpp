#include "../Thread.h"

using namespace NoiseKernel;

Task::Task(string taskName, vector<string> params, Thread* runningThread, void* data)
    : taskName(taskName), params(params), runningThread(runningThread), data(data)
{

}

Task::~Task()
{

}

string Task::getTaskName()
{
    return taskName;
}

string Task::getParam(int index)
{
    if (index >= params.size())
    {
        return "";
    }

    return params.at(index);
}

vector<string> Task::getParams()
{
    return params;
}

Thread* Task::getRunningThread()
{
    return runningThread;
}

void* Task::getData()
{
    return data;
}

