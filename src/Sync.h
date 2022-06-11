#ifndef Sync_h__
#define Sync_h__

#include <string>
#include <pthread.h>

using namespace std;

namespace NoiseKernel
{
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
}

#endif // Sync_h__
