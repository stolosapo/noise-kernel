#ifndef Thread_h__
#define Thread_h__

#include <string>
#include <pthread.h>
#include <map>

#include "Queue.h"
#include "Sync.h"

using namespace std;

namespace NoiseKernel
{
    typedef void* (*ThreadDelegate)(void* context);

    class Thread
    {
    private:
        pthread_t _thread;

        ThreadDelegate delegate;

        long long id;
        int poolIndex;
        bool dispose;
        bool running;

        static void* delegateInterceptor(void *);

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

    class ThreadInterceptionData
    {
    private:
        Thread* th;
        ThreadDelegate delegate;
        void* data;

    public:
        ThreadInterceptionData(Thread* th, ThreadDelegate delegate, void* data);
        virtual ~ThreadInterceptionData();

        virtual Thread* getThread();
        virtual ThreadDelegate getDelegate();
        virtual void* getData();
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

}

#endif // Thread_h__
