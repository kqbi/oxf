#*******************************************************************************
# Licensed Materials - Property of IBM
# (c) Copyright IBM Corporation 2008, 2011. All Rights Reserved.
#
# Note to U.S. Government Users Restricted Rights:  
# Use, duplication or disclosure restricted by GSA ADP Schedule 
# Contract with IBM Corp.
#*******************************************************************************
ifeq ($(CPU),)
CPU=
LIB_PREFIX=linux
CC=gcc
AR=ar
else
CPU=$(CPU)
LIB_PREFIX=$(LIB_PREFIX)
CC=$(CPU)-gcc
AR=$(CPU)-ar
endif

PATH_SEP=/
RM=rm -fr
CP=cp
RHAP_FLAGS=
ARFLAGS=-rvu

DEFAULT_CPP_FLAGS=-g

ifeq ($(LIB_PREFIX),mvl)
OM_MC_SUPPORT=-DOM_NO_MC_SUPPORT
else
OM_MC_SUPPORT=
endif

ADDED_CPP_FLAGS = $(DEFAULT_CPP_FLAGS) $(OM_MC_SUPPORT) -I.. -I../osconfig/Linux -DUSE_IOSTREAM  $(RHAP_FLAGS)

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
all: $(LIB_PREFIX)$(CFG)$(CPU).a

else
ifeq ($(CFG),oxfinst)
RHAP_FLAGS:=-D_OMINSTRUMENT
all: $(LIB_PREFIX)$(CFG)$(CPU).a

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

SRCS = linuxos$(CPP_EXT) \
  $(OXF_SRC)

HDRS = linuxos$(H_EXT) \
  $(OXF_INC)

OBJS = linuxos$(OBJ_EXT) \
  $(OXF_OBJ)

define BUILD_LIB
$(AR) $(ARFLAGS) $@ $?
$(CP) $@  ..$(PATH_SEP)lib$(PATH_SEP)$@
$(RM) $(OBJS) $@
endef

$(LIB_PREFIX)$(CFG)$(CPU).a: $(OBJS)
	$(BUILD_LIB)





