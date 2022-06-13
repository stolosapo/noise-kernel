AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = $(ACLOCAL_FLAGS)

bin_PROGRAMS = noisekernel

mainincludedir = $(includedir)/noisekernel
maininclude_HEADERS = \
    Argument.h \
    Signal.h \
    Observer.h \ 
    Thread.h \
    Queue.h \
    Strategy.h

common_sources = \
    Queue.h \
    Strategy.h \
    \
    argument/Argument.cpp \
    argument/ArgumentAdapter.cpp \
    argument/ArgumentList.cpp \
    argument/ArgumentParser.cpp \
    argument/ArgumentProvider.cpp \
    argument/MockAdapter.h argument/MockAdapter.cpp \
    \
    signal/Signal_SIGINT.cpp \
    signal/Signal.cpp \
    signal/SignalAdapter.cpp \
    signal/SignalHandler.cpp \
    \
    observer/Event.cpp \
    observer/EventArgs.cpp \
    observer/EventHandler.cpp \
    \
    thread/Barrier.cpp \
    thread/Locker.cpp \
    thread/TaskContext.cpp \
    thread/TaskRunner.cpp \
    thread/Thread.cpp \
    thread/ThreadInterceptionData.h thread/ThreadInterceptionData.cpp \
    thread/ThreadPool.cpp \
    \
    utils/StringHelper.h utils/StringHelper.cpp


noisekernel_SOURCES = main.cpp $(common_sources)
noisekernel_LDADD = libnoisekernel.la
noisekernel_CXXFLAGS = $(AM_CXXFLAGS)

lib_LTLIBRARIES = libnoisekernel.la
libnoisekernel_la_LDFLAGS = -version-info 1:0:0 -pthread
libnoisekernel_la_CXXFLAGS = $(AM_CXXFLAGS) -pthread
libnoisekernel_la_SOURCES = $(common_sources)

TESTS = noisekernel
