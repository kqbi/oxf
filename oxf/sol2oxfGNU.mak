#*******************************************************************************
# Licensed Materials - Property of IBM
# (c) Copyright IBM Corporation 2008, 2014. All Rights Reserved.
#
# Note to U.S. Government Users Restricted Rights:  
# Use, duplication or disclosure restricted by GSA ADP Schedule 
# Contract with IBM Corp.
#*******************************************************************************
PATH_SEP=/
CC=gcc
RM=rm -fr
CP=cp
RHAP_FLAGS=
AR=ar
ARFLAGS=-rvu
DEFAULT_CPP_FLAGS=-g -fPIC
ADDED_CPP_FLAGS = $(DEFAULT_CPP_FLAGS) -I/usr/include -I.. -I../osconfig/Solaris2 -DUSE_IOSTREAM  $(RHAP_FLAGS)

targets=oxf oxfinst

.DEFAULT : all

.PHONY : all

.FAILED :
	$(RM) $(OBJS)


.SUFFIXES: .cpp

.cpp.o:
	$(CC) $(ADDED_CPP_FLAGS) $(CPPFLAGS) -c $<

ifeq ($(CFG),oxf)
RHAP_FLAGS:=
all: sol2$(CFG)GNU.a

else
ifeq ($(CFG),oxfinst)
RHAP_FLAGS:=-D_OMINSTRUMENT
all: sol2$(CFG)GNU.a

else
all :
	@echo "Usage: $(MAKE) all CFG=<target>."
	@echo "where target is one of $(targets)"
endif
endif

CPP_EXT=.cpp
H_EXT=.h
OBJ_EXT=.o

include oxfFiles.list

SRCS = sol2os$(CPP_EXT) \
  $(OXF_SRC)

HDRS = sol2os$(H_EXT) \
  $(OXF_INC)

OBJS = sol2os$(OBJ_EXT) \
  $(OXF_OBJ)

define BUILD_LIB
$(AR) $(ARFLAGS) $@ $?
$(CP) $@  ..$(PATH_SEP)lib$(PATH_SEP)$@
$(RM) $(OBJS) $@
endef

sol2oxfGNU.a: $(OBJS)
	$(BUILD_LIB)

sol2oxfinstGNU.a: $(OBJS)
	$(BUILD_LIB)






