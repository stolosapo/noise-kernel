#include "ThreadContext.h"

using namespace NoiseKernel;

ThreadContext::ThreadContext(Thread* th, ThreadDelegate delegate, void* data)
    : th(th), delegate(delegate), data(data)
{

}

ThreadContext::~ThreadContext()
{

}

Thread* ThreadContext::getThread()
{
    return th;
}

ThreadDelegate ThreadContext::getDelegate()
{
    return delegate;
}

void* ThreadContext::getData()
{
    return data;
}
