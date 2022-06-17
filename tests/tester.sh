#!/bin/sh

g++ -g -c -o main.o main.cpp
g++ -g -c -o MainTestSuite.o MainTestSuite.cpp
g++ -g -c -o ArgumentListTest.o argument/ArgumentListTest.cpp
g++ -g -c -o ArgumentParserTest.o argument/ArgumentParserTest.cpp
g++ -g -c -o ArgumentProviderTest.o argument/ArgumentProviderTest.cpp
g++ -g -c -o ArgumentAdapterTest.o argument/ArgumentAdapterTest.cpp
g++ -g -c -o SignalAdapterTest.o signal/SignalAdapterTest.cpp
g++ -g -c -o EventTest.o observer/EventTest.cpp
g++ -g -c -o MockDelegate.o observer/MockDelegate.cpp
g++ -g -c -o MockEventHandler.o observer/MockEventHandler.cpp
g++ -g -c -o MockSender.o observer/MockSender.cpp
g++ -g -c -o ThreadPoolTest.o thread/ThreadPoolTest.cpp
g++ -g -c -o ThreadTest.o thread/ThreadTest.cpp
g++ -g -c -o TaskRunnerTest.o thread/TaskRunnerTest.cpp

g++ -g -c -o StringHelper.o ../src/utils/StringHelper.cpp

g++ -g -c -o Argument.o ../src/argument/Argument.cpp
g++ -g -c -o ArgumentAdapter.o ../src/argument/ArgumentAdapter.cpp
g++ -g -c -o ArgumentList.o ../src/argument/ArgumentList.cpp
g++ -g -c -o ArgumentParser.o ../src/argument/ArgumentParser.cpp
g++ -g -c -o ArgumentProvider.o ../src/argument/ArgumentProvider.cpp
g++ -g -c -o MockAdapter.o ../src/argument/MockAdapter.cpp

g++ -g -c -o Signal_SIGINT.o ../src/signal/Signal_SIGINT.cpp
g++ -g -c -o Signal.o ../src/signal/Signal.cpp
g++ -g -c -o SignalAdapter.o ../src/signal/SignalAdapter.cpp
g++ -g -c -o SignalHandler.o ../src/signal/SignalHandler.cpp

g++ -g -c -o Event.o ../src/observer/Event.cpp
g++ -g -c -o EventArgs.o ../src/observer/EventArgs.cpp
g++ -g -c -o EventHandler.o ../src/observer/EventHandler.cpp

g++ -g -c -o Barrier.o ../src/thread/Barrier.cpp
g++ -g -c -o Locker.o ../src/thread/Locker.cpp
g++ -g -c -o Task.o ../src/thread/Task.cpp
g++ -g -c -o TaskRunner.o ../src/thread/TaskRunner.cpp
g++ -g -c -o Thread.o ../src/thread/Thread.cpp
g++ -g -c -o ThreadContext.o ../src/thread/ThreadContext.cpp
g++ -g -c -o ThreadPool.o ../src/thread/ThreadPool.cpp

g++ main.o \
    \
    StringHelper.o \
    \
    Argument.o \
    ArgumentAdapter.o \
    ArgumentList.o \
    ArgumentParser.o \
    ArgumentProvider.o \
    \
    Signal_SIGINT.o \
    Signal.o \
    SignalAdapter.o \
    SignalHandler.o \
    \
    Event.o \
    EventArgs.o \
    EventHandler.o \
    \
    Barrier.o \
    Locker.o \
    Task.o \
    TaskRunner.o \
    Thread.o \
    ThreadContext.o \
    ThreadPool.o \
    \
    MainTestSuite.o \
    MockAdapter.o \
    ArgumentListTest.o \
    ArgumentParserTest.o \
    ArgumentProviderTest.o \
    ArgumentAdapterTest.o \
    SignalAdapterTest.o \
    ThreadPoolTest.o \
    ThreadTest.o \
    TaskRunnerTest.o \
    \
    EventTest.o\
    MockDelegate.o\
    MockEventHandler.o\
    MockSender.o\
    \
    -o tester -pthread -lnoisetest

./tester
