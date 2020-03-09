#*******************************************************************************
# Licensed Materials - Property of IBM
# (c) Copyright IBM Corporation 2008, 2014. All Rights Reserved.
#
# Note to U.S. Government Users Restricted Rights:  
# Use, duplication or disclosure restricted by GSA ADP Schedule 
# Contract with IBM Corp.
#*******************************************************************************
CACHE_DIR=./SunWS_cache
CC=CC -mt -g -KPIC
RM=rm -fr
CP=cp
RHAP_FLAGS=
ADDED_CPP_FLAGS = -I.. -I../osconfig/Solaris2 -DUSE_IOSTREAM $(RHAP_FLAGS)

targets=sol2oxf.a sol2oxfinst.a 

.PHONY: $(targets)

.FAILED:
	$(RM) $(OBJS)


.SUFFIXES: .cpp

.cpp.o:
	$(CC) $(ADDED_CPP_FLAGS) $(CPPFLAGS) -c $<

all :
	@echo Usage\: $(MAKE) "<target>".
	@echo where target is one of $(targets)

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

sol2oxf.a := RHAP_FLAGS=
sol2oxfinst.a := RHAP_FLAGS=-D_OMINSTRUMENT

$(targets) : $(OBJS)
	$(CC) -xar -o $@ $?
	$(CP) $@ ../lib/$@
	$(RM) $(OBJS) $@ $(TMPL_DIR) $(CACHE_DIR)





