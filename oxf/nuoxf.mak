#*******************************************************************************
# Licensed Materials - Property of IBM
# (c) Copyright IBM Corporation 2008, 2014. All Rights Reserved.
#
# Note to U.S. Government Users Restricted Rights:  
# Use, duplication or disclosure restricted by GSA ADP Schedule 
# Contract with IBM Corp.
#*******************************************************************************
####################
# Required settings
####################
# BUILD_SET (Debug or Release)
# CPU (the target BSP)
# ATI_DIR (the Nucleus environment root)
####################

targets=oxf oxfsim oxfinst oxfsiminst oxfinstt oxfsiminstt
CP=copy
RM=del
OBJ_EXT=.obj
CPP_EXT=.cpp
C_EXT=.c
H_EXT=.h
DEBUG_FLAGS=-g -DASSERT_DEBUG -DDEBUG 

CCOPTS= -v -D__DIAB -@E=Err.txt -c -t$(CPU) -DPLUS -DNET \
-Xforce-prototypes -Xmismatch-warning -Xno-common -Xno-exception -Xno-rtti \
-I./ -I$(ATI_DIR)/plus -I$(ATI_DIR)/net/inc -I$(ATI_DIR) -I../ -I../osconfig/Nucleus/ \ 

COPTS=  -v -D__DIAB -c -t$(CPU) -DPLUS -DNET \
-Xforce-prototypes -Xmismatch-warning -Xno-common \
-I./ -I$(ATI_DIR)/plus -I$(ATI_DIR)/net/inc -I$(ATI_DIR) -I../ \ 

.SUFFIXES: .cpp

.IF "$(BUILD_SET)" == "Debug"
CCOPTS+=$(DEBUG_FLAGS)
COPTS+=$(DEBUG_FLAGS)
LIB_POSTFIX=
ASMOPTS=-g
.ELIF "$(BUILD_SET)" == "Release"
LIB_POSTFIX=R
ASMOPTS=
.ELSE
build_set_check:
	@[
	@echo.
	@echo ERROR: An invalid BUILD_SET is specified.
	@echo Please specify BUILD_SET=Debug or BUILD_SET=Release
	@echo.
	@echo Build Aborted!
	]
.ENDIF

.IF "$(ATI_DIR)" == ""
ati_dir_check:
	@[
	@echo.
	@echo ERROR: Please set the ATI_DIR environment variable to point to
	@echo        your Nucleus Plus installation directory.
	@echo. 
	@echo Cannot find Nucleus Plus header files.
	@echo Build Aborted!
	]
.ENDIF

.IF "$(CPU)" == ""
CPU_check:
	@[
	@echo.
	@echo ERROR: Must set CPU processor in CPU variable.
	@echo.
	@echo Build Aborted!
	]
.ENDIF




.IF "$(CFG)" == "oxf"
TARGET_NAME=Nuoxf
RHAP_FLAGS=-DUSE_IOSTREAM
CCOPTS+=$(RHAP_FLAGS)
all: $(TARGET_NAME)$(LIB_POSTFIX).lib
.ELIF "$(CFG)" == "oxfsim"
TARGET_NAME=Nuoxfsim
RHAP_FLAGS=-D_SIM_TIMER -DUSE_IOSTREAM
CCOPTS+=$(RHAP_FLAGS)
all: $(TARGET_NAME)$(LIB_POSTFIX).lib
.ELIF "$(CFG)" == "oxfinst"
TARGET_NAME=Nuoxfinst
RHAP_FLAGS=-D_OMINSTRUMENT -DUSE_IOSTREAM
CCOPTS+=$(RHAP_FLAGS)
all: $(TARGET_NAME)$(LIB_POSTFIX).lib
.ELIF "$(CFG)" == "oxfsiminst"
TARGET_NAME=Nuoxfsiminst
RHAP_FLAGS=-D_OMINSTRUMENT -D_SIM_TIMER -DUSE_IOSTREAM
CCOPTS+=$(RHAP_FLAGS)
all: $(TARGET_NAME)$(LIB_POSTFIX).lib
.ELIF "$(CFG)" == "oxfinstt"
TARGET_NAME=Nuoxfinstt
RHAP_FLAGS=-D_OMINSTRUMENT -DUSE_IOSTREAM -DNU_OMTRACER
CCOPTS+=$(RHAP_FLAGS)
COPTS+=-DNU_OMTRACER
all: $(TARGET_NAME)$(LIB_POSTFIX).lib
.ELIF "$(CFG)" == "oxfsiminstt"
TARGET_NAME=Nuoxfsiminstt
RHAP_FLAGS=-D_OMINSTRUMENT -D_SIM_TIMER -DUSE_IOSTREAM -DNU_OMTRACER
CCOPTS+=$(RHAP_FLAGS)
COPTS+=-DNU_OMTRACER
all: $(TARGET_NAME)$(LIB_POSTFIX).lib

.ELSE
all:
	@[
	@echo.
	@echo "Usage: $(MAKE) CFG=<target> BUILD_SET=Debug|Release CPU=PROCESSOR ATI_DIR=Nucleus Dir
	@echo where target is one of $(targets)
	@echo.
	]
.ENDIF

.cpp.obj : 
	dplus $(CCOPTS) -o $*.obj $<

.c.obj : 
	dcc $(COPTS) -o $*.obj $<

.s.obj:
	das $(ASMOPTS) -o $*.obj $<

libDir :
	+if not exist "$(LIB_DIR)/$(NULL)" mkdir "$(LIB_DIR)"

include oxfFiles.list

SRCS = NuOS$(CPP_EXT) \
 NuInit$(C_EXT) \
 $(OXF_SRC) 

HDRS = NuOS$(H_EXT) \
 NuInit$(H_EXT) \
 $(OXF_INC) 
  
OBJS = NuOS$(OBJ_EXT) \
 NuInit$(OBJ_EXT) \
 $(OXF_OBJ)
 

$(TARGET_NAME)$(LIB_POSTFIX).lib : $(OBJS)
	dar -r $@ $(OBJS)
	dar -sR $@      
	+$(CP) $@ ..\lib\$@
	+$(RM) $(OBJS) $@

