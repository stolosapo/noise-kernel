#include "EventTest.h"
#include "../../src/Observer.h"
#include "MockSender.h"
#include "MockEventHandler.h"
#include "MockDelegate.h"
#include <noisetest/Assertion.h>

using namespace NoiseTest;
using namespace NoiseKernel;

EventTest::EventTest(): UnitTestSuite("Event Test Suite", 0)
{

}

EventTest::~EventTest()
{

}

void EventTest::registerTests()
{
    registerTest("Add Event Handler passing EventHandler", &test_event_add_event_handler__with_handler);
	registerTest("Add Event Handler passing Delegate", &test_event_add_event_handler__with_delegate);

	registerTest("Remove Event Handler passing EventHandler", &test_event_remove_event_handler__with_handler);
	registerTest("Remove Event Handler passing Delegate", &test_event_remove_event_handler__with_delegate);

	registerTest("Add Event Handler using += passing EventHandler", &test_event_add_event_handler__with_handler_and_operator);
	registerTest("Add Event Handler using += passing Delegate", &test_event_add_event_handler__with_delegate_and_operator);

	registerTest("Remove Event Handler using -= passing EventHandler", &test_event_remove_event_handler__with_handler_and_operator);
	registerTest("Remove Event Handler using -= passing Delegate", &test_event_remove_event_handler__with_delegate_and_operator);
}

void test_event_add_event_handler__with_handler()
{
	MockSender* sender = new MockSender;

	Event event;

	event.addEventHandler(new MockEventHandler);
	event.addEventHandler(new MockEventHandler);

	event.raise(sender, new EventArgs);

	assertEqual(sender->counter, 2);
}

void test_event_add_event_handler__with_delegate()
{
	MockSender* sender = new MockSender;

	Event event;

	event.addEventHandler(&mockDelegate);
	event.addEventHandler(&mockDelegate);

	event.raise(sender, new EventArgs);

	assertEqual(sender->counter, 2);
}

void test_event_remove_event_handler__with_handler()
{
	MockSender* sender = new MockSender;

	MockEventHandler* h1 = new MockEventHandler;
	MockEventHandler* h2 = new MockEventHandler;

	Event event;

	event.addEventHandler(h1);
	event.addEventHandler(h2);

	event.removeEventHandler(h1);
	event.removeEventHandler(h2);

	event.raise(sender, new EventArgs);

	assertEqual(sender->counter, 0);
}

void test_event_remove_event_handler__with_delegate()
{
	MockSender* sender = new MockSender;

	EventDelegate d1 = &mockDelegate;
	EventDelegate d2 = &mockDelegate;

	Event event;

	event.addEventHandler(d1);
	event.addEventHandler(d2);

	event.removeEventHandler(d1);
	event.removeEventHandler(d2);

	event.raise(sender, new EventArgs);

	assertEqual(sender->counter, 0);
}

void test_event_add_event_handler__with_handler_and_operator()
{
	MockSender* sender = new MockSender;

	Event event;

	event += new MockEventHandler;
	event += new MockEventHandler;

	event.raise(sender, new EventArgs);

	assertEqual(sender->counter, 2);
}

void test_event_add_event_handler__with_delegate_and_operator()
{
	MockSender* sender = new MockSender;

	Event event;

	event += &mockDelegate;
	event += &mockDelegate;

	event.raise(sender, new EventArgs);

	assertEqual(sender->counter, 2);
}

void test_event_remove_event_handler__with_handler_and_operator()
{
	MockSender* sender = new MockSender;

	MockEventHandler* h1 = new MockEventHandler;
	MockEventHandler* h2 = new MockEventHandler;

	Event event;

	event += h1;
	event += h2;

	event -= h1;
	event -= h2;

	event.raise(sender, new EventArgs);

	assertEqual(sender->counter, 0);
}

void test_event_remove_event_handler__with_delegate_and_operator()
{
	MockSender* sender = new MockSender;

	EventDelegate d1 = &mockDelegate;
	EventDelegate d2 = &mockDelegate;

	Event event;

	event += d1;
	event += d2;

	event -= d1;
	event -= d2;

	event.raise(sender, new EventArgs);

	assertEqual(sender->counter, 0);
}
