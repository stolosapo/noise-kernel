#include "../Thread.h"

using namespace NoiseKernel;

Locker::Locker()
{

}

Locker::~Locker()
{

}

int Locker::init()
{
    return pthread_mutex_init(&_mutex, NULL);
}

int Locker::lock()
{
    return pthread_mutex_lock(&_mutex);
}

int Locker::unlock()
{
    return pthread_mutex_unlock(&_mutex);
}

int Locker::destroy()
{
    return pthread_mutex_destroy(&_mutex);
}
