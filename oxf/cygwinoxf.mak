#*******************************************************************************
# Licensed Materials - Property of IBM
# (c) Copyright IBM Corporation 2008, 2014. All Rights Reserved.
#
# Note to U.S. Government Users Restricted Rights:  
# Use, duplication or disclosure restricted by GSA ADP Schedule 
# Contract with IBM Corp.
#*******************************************************************************
PATH_SEP=/
CC=g++
RM=rm -fr
CP=cp
RHAP_FLAGS=
AR=ar
ARFLAGS=-rvu
DEFAULT_CPP_FLAGS=-g
ADDED_CPP_FLAGS = $(DEFAULT_CPP_FLAGS) -I.. -I../osconfig/Cygwin -DCYGWIN $(RHAP_FLAGS)
CPU=
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
all: cygwin$(CFG)$(CPU).a

else
ifeq ($(CFG),oxfinst)
RHAP_FLAGS:=-D_OMINSTRUMENT
all: cygwin$(CFG)$(CPU).a

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

SRCS = ntos$(CPP_EXT) \
  $(OXF_SRC)

HDRS = ntos$(H_EXT) \
  $(OXF_INC)

OBJS = ntos$(OBJ_EXT) \
  $(OXF_OBJ)

define BUILD_LIB
$(AR) $(ARFLAGS) $@ $?
$(CP) $@  ..$(PATH_SEP)lib$(PATH_SEP)$@
$(RM) $(OBJS) $@
endef

cygwin$(CFG)$(CPU).a: $(OBJS)
	$(BUILD_LIB)






