#ifndef Thread_h__
#define Thread_h__

#include <string>
#include <vector>
#include <pthread.h>
#include <map>

#include "Queue.h"
#include "Strategy.h"

using namespace std;

namespace NoiseKernel
{
    typedef void* (*ThreadDelegate)(void* data);

    class Locker
    {
    private:
        pthread_mutex_t _mutex;

    public:
        Locker();
        virtual ~Locker();

        virtual int init();
        virtual int lock();
        virtual int unlock();
        virtual int destroy();
    };

    class Barrier
    {
    private:
        pthread_barrier_t _barrier;

        int number;

    public:
        Barrier(int number);
        virtual ~Barrier();

        virtual int init();
        virtual int wait();
        virtual int destroy();
    };

    class Thread
    {
    private:
        pthread_t _thread;

        ThreadDelegate delegate;

        long long id;
        int poolIndex;
        bool dispose;
        bool running;

        static void* delegateThreadContext(void *);

        void setId(long long id);
        void setSelfId();
        void setName(const char* name);
        void setMustDispose(bool dispose);

    public:
        Thread();
        Thread(int poolIndex);
        virtual ~Thread();

        virtual void attachDelegate(ThreadDelegate delegate);
        virtual void detachDelegate(ThreadDelegate delegate);

        virtual bool start(void* data);
        virtual bool start(void* data, const char* name);
        virtual void wait();
        virtual void* result();
        virtual bool cancel();
        virtual bool detach();
        virtual void* exit();

        virtual long long self();

        long long getId();
        int getPoolIndex();
        string getStringId();
        bool mustDispose();
        bool isRunning();

        Thread& operator+=(ThreadDelegate delegate);
        Thread& operator-=(ThreadDelegate delegate);
    };

    class ThreadPool
    {
    private:
        int poolSize;

        Locker locker;

        Queue<Thread> pool;
        map<Thread*, Thread*> usedThreads;

    protected:
        void init();
        void clear();

    public:
        ThreadPool(int poolSize);
        virtual ~ThreadPool();

        bool hasNext();
        bool reachSize();
        Thread* getNext();
        void putBack(Thread* thread);

        int numberOfActiveThreads();
    };

    class Task
    {
    private:
        string taskName;
        vector<string> params;
        Thread *runningThread;
        void* data;

    public:
        Task(string taskName, vector<string> params, Thread* runningThread, void* data);
        virtual ~Task();

        string getTaskName();
        string getParam(int index);
        vector<string> getParams();
        Thread* getRunningThread();
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
        virtual void* runTask(string task, void* data);
    };

}

#endif // Thread_h__
