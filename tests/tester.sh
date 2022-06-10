#!/bin/sh

g++ -g -c -o main.o main.cpp
g++ -g -c -o MainTestSuite.o MainTestSuite.cpp
g++ -g -c -o ArgumentListTest.o argument/ArgumentListTest.cpp
g++ -g -c -o ArgumentParserTest.o argument/ArgumentParserTest.cpp
g++ -g -c -o ArgumentProviderTest.o argument/ArgumentProviderTest.cpp
g++ -g -c -o ArgumentAdapterTest.o argument/ArgumentAdapterTest.cpp
g++ -g -c -o SignalAdapterTest.o signal/SignalAdapterTest.cpp

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
    MainTestSuite.o \
    MockAdapter.o \
    ArgumentListTest.o \
    ArgumentParserTest.o \
    ArgumentProviderTest.o \
    ArgumentAdapterTest.o \
    SignalAdapterTest.o \
    \
    -o tester -lnoisetest

./tester
