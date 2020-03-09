#*******************************************************************************
# Licensed Materials - Property of IBM
# (c) Copyright IBM Corporation 2008, 2012. All Rights Reserved.
#
# Note to U.S. Government Users Restricted Rights:  
# Use, duplication or disclosure restricted by GSA ADP Schedule 
# Contract with IBM Corp.
#*******************************************************************************
CPU = PENTIUM
TOOL = diab
TGT_DIR = $(WIND_BASE)/target

POWER_MGMT_FLAG=-DOM_SUPPORT_POWER_MGMT
ifeq ($(CPU), SIMNT)
POWER_MGMT_FLAG=
else
ifeq ($(CPU), SIMPENTIUM)
POWER_MGMT_FLAG=
else
ifeq ($(CPU), SIMLINUX)
POWER_MGMT_FLAG=
endif
endif
endif

LIB_SUFFIX = $(TOOL)

ifeq ($(VX_VER),5.5)
OM_VX_FLAGS=-D_WRS_KERNEL
else
OM_VX_FLAGS=
endif
TOOL_FAMILY=diab
SEMAPHORE_WARNING=
ifeq ($(TOOL_FAMILY),diab)
SEMAPHORE_WARNING=-ei5386
endif 

ifeq ($(RTP_MODE),TRUE)
RTP_SUFFIX=_RTP_
RULES_LIBRARY_ROOT=$(WIND_USR)
else
RTP_SUFFIX=
RULES_LIBRARY_ROOT=$(TGT_DIR)/h
endif

OM_OPT_LEVEL = -O
ADDED_C++FLAGS = $(OM_OPT_LEVEL) $(OM_VX_FLAGS) $(SEMAPHORE_WARNING) -I.. -I../osconfig/VxWorks -DVxWorks $(RHAP_FLAGS) $(POWER_MGMT_FLAG)

.DEFAULT : all

include $(RULES_LIBRARY_ROOT)/make/rules.library

targets=vxoxf vxoxfinst 

.PHONY : all


.FAILED :
	$(RM) $(OBJS)


CPP_EXT=.cpp
H_EXT=.h
OBJ_EXT=.o

include oxfFiles.list

SRCS = VxOS$(CPP_EXT) \
  $(OXF_SRC)

HDRS = VxOS$(H_EXT) \
  $(OXF_INC)

OBJS = VxOS$(OBJ_EXT) \
  $(OXF_OBJ)


ifeq ($(TOOL_FAMILY),diab)
define BUILD_LIB
$(AR) $(ARFLAGS) $@ $?
$(CP) $@  ..$(PATH_SEP)lib$(PATH_SEP)$@
$(RM) $(OBJS) $@
endef
else
define BUILD_LIB
$(AR) $(ARFLAGS) $@ $?
$(CP) $@  ..$(PATH_SEP)lib$(PATH_SEP)$@
$(RANLIB) ..$(PATH_SEP)lib$(PATH_SEP)$@
$(RM) $(OBJS) $@
endef
endif


$(CFG)$(CPU)$(RTP_SUFFIX)$(LIB_SUFFIX).a: $(OBJS)
	$(BUILD_LIB)

ifeq ($(PATH_SEP),)
all :
	@echo PATH_SEP is not defined. Please define it as \\ or /
else
ifeq ($(CFG),vxoxf)
RHAP_FLAGS=-D_OM_NO_IOSTREAM
all : $(CFG)$(CPU)$(RTP_SUFFIX)$(LIB_SUFFIX).a
else
ifeq ($(CFG),vxoxfinst)
RHAP_FLAGS=-DUSE_IOSTREAM -D_OMINSTRUMENT
all : $(CFG)$(CPU)$(RTP_SUFFIX)$(LIB_SUFFIX).a
else
all :
	@echo Usage: $(MAKE) all "CFG=<target>".
	@echo where target is one of $(targets)
endif
endif
endif
