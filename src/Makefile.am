LIBEZPARSE_LIBADD = -lm

lib_LTLIBRARIES = libezparse.la
include_HEADERS = ezparse.h
libezparse_la_LIBADD = $(LIBEZPARSE_LIBADD)

#bin_PROGRAMS = ezparse-test
#ezparse_test_LDADD = libezparse.la $(LIBEZPARSE_LIBADD) -lnova -lrestart

AM_CPPFLAGS = -D__STDC_INT64__

SUBDIRS = ../glitter
AM_CPPFLAGS += -I ../glitter/src
