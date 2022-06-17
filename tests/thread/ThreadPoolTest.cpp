#include "ThreadPoolTest.h"
#include "../../src/Thread.h"
#include <noisetest/Assertion.h>

using namespace NoiseTest;
using namespace NoiseKernel;

ThreadPoolTest::ThreadPoolTest(): UnitTestSuite("Thread Pool Test Suite", 0)
{

}

ThreadPoolTest::~ThreadPoolTest()
{

}

void ThreadPoolTest::registerTests()
{
    registerTest("Should method hasNext return correct results", &test_thread_pool_has_next);
	registerTest("Should method reachSize return correct results", &test_thread_pool_reach_size);
	registerTest("Should method getNext return correct results", &test_thread_pool_get_next);
	registerTest("Should method getNext use queue pop method to get next thread", &test_thread_pool_get_next_use_queue_pop);
	registerTest("Should method putBack stops putting threads when size reached", &test_thread_pool_put_back);
	registerTest("Should pool is syncronized", &test_thread_pool_multi_threading);
}

void test_thread_pool_has_next()
{
    ThreadPool* pool = new ThreadPool(3);

    Thread* t1;
    Thread* t2;
    Thread* t3;

    // 3
    assertTrue(pool->hasNext());


    // 2
    t1 = pool->getNext();
    assertTrue(pool->hasNext());

    
    // 1
    t2 = pool->getNext();
    assertTrue(pool->hasNext());


    // 0
    t3 = pool->getNext();
    assertFalse(pool->hasNext());


    // 1
    pool->putBack(t3);
    assertTrue(pool->hasNext());
}

void test_thread_pool_reach_size()
{
    ThreadPool* pool = new ThreadPool(3);

    Thread* t1;
    Thread* t2;
    Thread* t3;

    // 3
    assertTrue(pool->reachSize());


    // 2
    t1 = pool->getNext();
    assertFalse(pool->reachSize());

    
    // 1
    t2 = pool->getNext();
    assertFalse(pool->reachSize());


    // 0
    t3 = pool->getNext();
    assertFalse(pool->reachSize());


    // 1
    pool->putBack(t3);
    assertFalse(pool->reachSize());


    // 2
    pool->putBack(t2);
    assertFalse(pool->reachSize());


    // 3
    pool->putBack(t1);
    assertTrue(pool->reachSize());
}

void test_thread_pool_get_next()
{
    ThreadPool* pool = new ThreadPool(3);

    Thread* t1 = pool->getNext();
    Thread* t2 = pool->getNext();
    Thread* t3 = pool->getNext();
    Thread* t4 = pool->getNext();

    assertTrue(t1 != NULL);
    assertTrue(t2 != NULL);
    assertTrue(t3 != NULL);
    assertTrue(t4 == NULL);
}

void* t1_delegate(void* data)
{
    ((int*)data)[0] = 1;
    return NULL;
}

void* t2_delegate(void* data)
{
    ((int*)data)[0] = 2;
    return NULL;
}

void* t3_delegate(void* data)
{
    ((int*)data)[0] = 3;
    return NULL;
}

void* t4_delegate(void* data)
{
    ((int*)data)[0] = 4;
    return NULL;
}

void test_thread_pool_get_next_use_queue_pop()
{
    ThreadPool* pool = new ThreadPool(3);

    Thread* t1 = pool->getNext();
    Thread* t2 = pool->getNext();
    Thread* t3 = pool->getNext();
    
    t1->attachDelegate(&t1_delegate);
    t2->attachDelegate(&t2_delegate);
    t3->attachDelegate(&t3_delegate);

    pool->putBack(t3);
    pool->putBack(t2);
    pool->putBack(t1);

    int* id = new int[1];

    Thread* next;

    next = pool->getNext();
    next->start(id);
    next->wait();
    assertEqual(id[0], 3);
    pool->putBack(next);

    next = pool->getNext();
    next->start(id);
    next->wait();
    assertEqual(id[0], 2);
    pool->putBack(next);

    next = pool->getNext();
    next->start(id);
    next->wait();
    assertEqual(id[0], 1);
    pool->putBack(next);

    next = pool->getNext();
    next->start(id);
    next->wait();
    assertEqual(id[0], 3);
    pool->putBack(next);
}

void test_thread_pool_put_back()
{
    ThreadPool* pool = new ThreadPool(3);

    Thread* t1 = pool->getNext();
    Thread* t2 = pool->getNext();
    Thread* t3 = pool->getNext();
    Thread* t4 = new Thread;
    
    t1->attachDelegate(&t1_delegate);
    t2->attachDelegate(&t2_delegate);
    t3->attachDelegate(&t3_delegate);
    t4->attachDelegate(&t4_delegate);

    pool->putBack(t3);
    pool->putBack(t2);
    pool->putBack(t1);
    pool->putBack(t4);

    int* id = new int[1];

    Thread* next;
    
    next = pool->getNext();
    next = pool->getNext();
    next = pool->getNext();
    next = pool->getNext();

    assertTrue(next == NULL);
    assertFalse(pool->hasNext());


    Thread* _t1 = new Thread;
    Thread* _t2 = new Thread;
    Thread* _t3 = new Thread;

    _t1->attachDelegate(&t1_delegate);
    _t2->attachDelegate(&t2_delegate);
    _t3->attachDelegate(&t3_delegate);

    pool->putBack(_t2);
    pool->putBack(_t3);
    pool->putBack(_t1);

    assertTrue(pool->reachSize());

    next = pool->getNext();
    next->start(id);
    next->wait();

    assertEqual(id[0], 2);
}

void* multi_thread_delegate(void* data)
{
    long long t_id = pthread_self();

    ThreadPool* pool = (ThreadPool*) data;

    while(pool->hasNext())
    {
        Thread* t = pool->getNext();
        t->attachDelegate(&t1_delegate);

        int* id = new int[1];

        t->start(id);
        t->wait();

        // cout << t_id << ": " << id[0] << endl;
    }
    return NULL;
}

void test_thread_pool_multi_threading()
{
    Thread* t1 = new Thread;
    Thread* t2 = new Thread;

    t1->attachDelegate(&multi_thread_delegate);
    t2->attachDelegate(&multi_thread_delegate);

    ThreadPool* pool = new ThreadPool(10);

    t1->start(pool);
    t2->start(pool);

    t1->wait();
    t2->wait();
}
