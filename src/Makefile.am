AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#endif

#include Makefile-LIBADD.inc
dist_bin_SCRIPTS = libezparse_config

lib_LTLIBRARIES = libezparse.la
include_HEADERS = ezparse.h
libezparse_la_LIBADD = $(LIBEZPARSE_LIBADD)

#bin_PROGRAMS = ezparse-test
#ezparse_test_LDADD = libezparse.la $(LIBEZPARSE_LIBADD) -lnova -lrestart
