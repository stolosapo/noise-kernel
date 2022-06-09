#!/bin/sh

g++ -g -c -o main.o main.cpp
g++ -g -c -o MainTestSuite.o MainTestSuite.cpp
g++ -g -c -o ArgumentListTest.o argument/ArgumentListTest.cpp
g++ -g -c -o ArgumentParserTest.o argument/ArgumentParserTest.cpp
g++ -g -c -o ArgumentProviderTest.o argument/ArgumentProviderTest.cpp

g++ -g -c -o StringHelper.o ../src/utils/StringHelper.cpp

g++ -g -c -o Argument.o ../src/argument/Argument.cpp
g++ -g -c -o ArgumentAdapter.o ../src/argument/ArgumentAdapter.cpp
g++ -g -c -o ArgumentList.o ../src/argument/ArgumentList.cpp
g++ -g -c -o ArgumentParser.o ../src/argument/ArgumentParser.cpp
g++ -g -c -o ArgumentProvider.o ../src/argument/ArgumentProvider.cpp

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
    MainTestSuite.o \
    ArgumentListTest.o \
    ArgumentParserTest.o \
    ArgumentProviderTest.o \
    \
    -o tester -lnoisetest

./tester
