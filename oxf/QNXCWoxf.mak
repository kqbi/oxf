#*******************************************************************************
# Licensed Materials - Property of IBM
# (c) Copyright IBM Corporation 2008, 2011. All Rights Reserved.
#
# Note to U.S. Government Users Restricted Rights:  
# Use, duplication or disclosure restricted by GSA ADP Schedule 
# Contract with IBM Corp.
#*******************************************************************************
PATH_SEP=/

CPU=x86
CPU_SUFFIX=
CC=qcc
RM=rm -fr
CP=cp
CPU_FLAG=
RHAP_FLAGS=
AR=nto$(CPU)-ar
ARFLAGS=-rvu
DEFAULT_CPP_FLAGS=-g -w -lang-c++ 
ADDED_CPP_FLAGS = $(CPU_FLAG) $(DEFAULT_CPP_FLAGS) -I$(QNX_TARGET)\usr\include -I.. -I../osconfig/QNX -D_MSL_NO_VECTOR_BOOL -DUSE_IOSTREAM $(RHAP_FLAGS)

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
CPU_FLAG:= -Vgcc_nto$(CPU)$(CPU_SUFFIX)
all: QNXCW$(CFG)$(CPU)$(CPU_SUFFIX).a
else
ifeq ($(CFG),oxfinst)
RHAP_FLAGS:=-D_OMINSTRUMENT
CPU_FLAG:= -Vgcc_nto$(CPU)$(CPU_SUFFIX)
all: QNXCW$(CFG)$(CPU)$(CPU_SUFFIX).a
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

SRCS = QNXOS$(CPP_EXT) \
  $(OXF_SRC)

HDRS = QNXOS$(H_EXT) \
  $(OXF_INC)

OBJS = QNXOS$(OBJ_EXT) \
  $(OXF_OBJ)

define BUILD_LIB
$(AR) $(ARFLAGS) $@ $?
$(CP) $@  ..$(PATH_SEP)lib$(PATH_SEP)$@
$(RM) $(OBJS) $@
endef

QNXCWoxf$(CPU)$(CPU_SUFFIX).a: $(OBJS)
	$(BUILD_LIB)

QNXCWoxfinst$(CPU)$(CPU_SUFFIX).a: $(OBJS)
	$(BUILD_LIB)
