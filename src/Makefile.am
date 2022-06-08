AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = $(ACLOCAL_FLAGS)

bin_PROGRAMS = noisekernel

mainincludedir = $(includedir)/noisekernel
maininclude_HEADERS = \
    all_header_files.h

common_sources = \
    all_source_files.cpp

noisekernel_SOURCES = main.cpp $(common_sources)
noisekernel_LDADD = libnoisekernel.la
noisekernel_CXXFLAGS = $(AM_CXXFLAGS)

lib_LTLIBRARIES = libnoisekernel.la
libnoisekernel_la_LDFLAGS = -version-info 1:0:0 -pthread
libnoisekernel_la_CXXFLAGS = $(AM_CXXFLAGS) -pthread
libnoisekernel_la_SOURCES = $(common_sources)

TESTS = noisekernel