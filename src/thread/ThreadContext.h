#ifndef ThreadContext_h__
#define ThreadContext_h__

#include "../Thread.h"

namespace NoiseKernel
{
    class ThreadContext
    {
    private:
        Thread* th;
        ThreadDelegate delegate;
        void* data;

    public:
        ThreadContext(Thread* th, ThreadDelegate delegate, void* data);
        virtual ~ThreadContext();

        virtual Thread* getThread();
        virtual ThreadDelegate getDelegate();
        virtual void* getData();
    };
}

#endif // ThreadContext_h__
