#*******************************************************************************
# Licensed Materials - Property of IBM
# (c) Copyright IBM Corporation 2008, 2011. All Rights Reserved.
#
# Note to U.S. Government Users Restricted Rights:  
# Use, duplication or disclosure restricted by GSA ADP Schedule 
# Contract with IBM Corp.
#*******************************************************************************
CPU = SIMNT
TOOL = gnu

PATH_SEP=/
LIB_SUFFIX = $(TOOL)

TGT_DIR = $(WIND_BASE)/target

RULES_LIBRARY_ROOT=$(TGT_DIR)/h

ifeq ($(API),apex)
OMAPEX=-DOM_APEX
else
OMAPEX=
endif

CONFIG += exceptions

OM_OPT_LEVEL = -O

ADDED_C++FLAGS += $(OM_OPT_LEVEL) -I. -I.. -I../osconfig/Vx653 -I$(TGT_DIR)/vThreads/h $(OMAPEX) -DVxWorks $(RHAP_FLAGS) 

.DEFAULT : all

include $(RULES_LIBRARY_ROOT)/make/rules.library


targets=vx653oxf vx653oxfinst 

.PHONY : all


.FAILED :
	$(RM) $(OBJS)


CPP_EXT=.cpp
H_EXT=.h
OBJ_EXT=.o

include oxfFiles.list

SRCS = Vx653$(API)$(CPP_EXT) \
  $(OXF_SRC)

HDRS = Vx653$(API)$(H_EXT) \
  $(OXF_INC)

OBJS = Vx653$(API)$(OBJ_EXT) \
  $(OXF_OBJ)

define BUILD_LIB
$(AR) $(ARFLAGS) $@ $?
$(CP) $@  ..$(PATH_SEP)lib$(PATH_SEP)$@
$(RANLIB) ..$(PATH_SEP)lib$(PATH_SEP)$@
$(RM) $(OBJS) $@
endef

$(CFG)$(CPU)$(LIB_SUFFIX).a: $(OBJS)
	$(BUILD_LIB)

ifeq ($(PATH_SEP),)
all :
	@echo PATH_SEP is not defined. Please define it as \\ or /
else
ifeq ($(CFG),vx653oxf)
RHAP_FLAGS=-D_OM_NO_IOSTREAM
all : $(CFG)$(CPU)$(LIB_SUFFIX).a
else
ifeq ($(CFG),vx653oxfinst)
RHAP_FLAGS=-DUSE_IOSTREAM -D_OMINSTRUMENT
all : $(CFG)$(CPU)$(LIB_SUFFIX).a
else
all :
	@echo Usage: $(MAKE) all "CFG=<target>".
	@echo where target is one of $(targets)
endif
endif
endif
