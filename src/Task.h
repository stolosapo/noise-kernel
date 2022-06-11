#ifndef Task_h__
#define Task_h__

#include <string>
#include <vector>
#include "Thread.h"
#include "Strategy.h"

using namespace std;

namespace NoiseKernel
{
    class TaskContext
    {
    private:
        string task;
        vector<string> params;
        void* data;

    public:
        TaskContext(string task, vector<string> params, void* data);
        virtual ~TaskContext();

        string getTask();
        string getParam(int index);
        void* getData();
    };

    class TaskRunner
    {
    private:
        static const string TASK_DELIMITER;
        static const string PARAM_DELIMITER;

        ValueStrategy<string, ThreadDelegate> *tasks;

        string getTaskFromParametrizedCommand(string command);
        vector<string> getParamsFromParametrizedCommand(string command);

    public:
        TaskRunner();
        virtual ~TaskRunner();

        virtual void registerTask(string task, ThreadDelegate delegate);

        virtual bool taskExist(string task);
        virtual bool parametrizedTaskExist(string task);
        virtual Thread* startTask(string task, void* data);
        virtual Thread* startTask(ThreadDelegate delegate, void* data);
        virtual void startTaskDetached(string task, void* data);
        virtual void* runTask(string task, void* data);
        virtual void* runParametrizedTask(string task, void* data);

        virtual string list();
    };

}

#endif // Task_h__
