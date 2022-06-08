AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = $(ACLOCAL_FLAGS)

bin_PROGRAMS = noisekernel

mainincludedir = $(includedir)/noisekernel
maininclude_HEADERS = \
    Argument.h

common_sources = \
    argument/Argument.cpp \
    argument/ArgumentList.cpp \
    argument/ArgumentParser.cpp   


noisekernel_SOURCES = main.cpp $(common_sources)
noisekernel_LDADD = libnoisekernel.la
noisekernel_CXXFLAGS = $(AM_CXXFLAGS)

lib_LTLIBRARIES = libnoisekernel.la
libnoisekernel_la_LDFLAGS = -version-info 1:0:0 -pthread
libnoisekernel_la_CXXFLAGS = $(AM_CXXFLAGS) -pthread
libnoisekernel_la_SOURCES = $(common_sources)

TESTS = noisekernel