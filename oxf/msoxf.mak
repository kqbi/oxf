#*******************************************************************************
# Licensed Materials - Property of IBM
# (c) Copyright IBM Corporation 2008, 2013. All Rights Reserved.
#
# Note to U.S. Government Users Restricted Rights:  
# Use, duplication or disclosure restricted by GSA ADP Schedule 
# Contract with IBM Corp.
#*******************************************************************************
CP=copy
RM=del
!IF "$(OS)" == "Windows_NT"
NULL=
RM=del /q
!ELSE
NULL=nul
!ENDIF

OUTDIR=


LIB_DIR=..\lib
LIB_PREFIX=MS
LIBCRT_FLAG=/MD

STL_FLAGS=
COMPILE_FLAGS=
PDB_FLAGS=
WARNING_LEVEL=/W4

BUILD_SET=DEBUG
#BUILD_SET=RELEASE
USE_PDB=FALSE
USE_STL=FALSE
RHAP_FLAGS=

!IF "$(USE_STL)" == "TRUE"
STL_FLAGS=/D "OM_USE_STL"
LIB_PREFIX=MSStl
WARNING_LEVEL=/W3
!ENDIF

!IF "$(BUILD_SET)" == "DEBUG"
COMPILE_FLAGS=/Od /D "_DEBUG" $(LIBCRT_FLAG)d
LIB_POSTFIX=
!ELSEIF "$(BUILD_SET)" == "RELEASE"
COMPILE_FLAGS=/O2 /D "NDEBUG" $(LIBCRT_FLAG)
WARNING_LEVEL=/W3
LIB_POSTFIX=R
!ELSE
!MESSAGE An invalid BUILD_SET "$(BUILD_SET)" is specified.
!MESSAGE Please specify BUILD_SET=DEBUG or BUILD_SET=RELEASE
!ERROR Existing
!ENDIF


!IF "$(USE_PDB)" == "TRUE"
PDB_FLAGS=/Zi /Fd"$(LIB_NAME)"
!ENDIF

LIB_CMD=link.exe -lib
LIB_FLAGS=/nologo


LIB_EXT=.lib
PDB_EXT=.pdb
OBJ_EXT=.obj
CPP_EXT=.cpp
H_EXT=.h


CPPFLAGS= /I . /I .. /I ../osconfig/WIN32
CPPFLAGS=$(CPPFLAGS) /nologo $(WARNING_LEVEL) $(ENABLE_EH) /Zl
CPPFLAGS=$(CPPFLAGS) /D "_AFXDLL" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_WINDOWS"
CPPFLAGS=$(CPPFLAGS) $(COMPILE_FLAGS)
CPPFLAGS=$(CPPFLAGS) $(PDB_FLAGS)
CPPFLAGS=$(CPPFLAGS) $(STL_FLAGS)
CPPFLAGS=$(CPPFLAGS) $(RHAP_FLAGS)
CPPFLAGS=$(CPPFLAGS) $(CRT_FLAGS)

.DEFAULT : ALL

.PHONY : ALL

!INCLUDE "oxfFiles.list"

SRCS = ntos$(CPP_EXT) \
  $(OXF_SRC)

HDRS = ntos$(H_EXT) \
  $(OXF_INC)

OBJS = ntos$(OBJ_EXT) \
  $(OXF_OBJ)

TARGETS=oxf oxfinst


libDir :
    if not exist "$(LIB_DIR)/$(NULL)" mkdir "$(LIB_DIR)"


LIB_NAME=$(LIB_PREFIX)$(TARGET_NAME)$(LIB_POSTFIX)

!IF "$(CFG)" == "oxf"
TARGET_NAME=oxf
RHAP_FLAGS=
ALL: $(LIB_NAME)$(LIB_EXT)
!ELSEIF "$(CFG)" == "oxfinst"
TARGET_NAME=oxfinst
RHAP_FLAGS=-D_OMINSTRUMENT
ALL: $(LIB_NAME)$(LIB_EXT)
!ELSE
!MESSAGE Usage: $(MAKE) all CFG=<target>.
!MESSAGE where target is one of $(TARGETS)
ALL:

!ENDIF


$(LIB_NAME)$(LIB_EXT): libDir $(OBJS)
	$(LIB_CMD) $(LIB_FLAGS) /out:$(LIB_NAME)$(LIB_EXT) $(OBJS)
	$(CP) $(LIB_NAME)$(LIB_EXT) $(LIB_DIR)
	if exist $(LIB_NAME)$(PDB_EXT) $(CP) $(LIB_NAME)$(PDB_EXT) $(LIB_DIR)
	if exist *$(OBJ_EXT) $(RM) *$(OBJ_EXT)
	if exist $(LIB_NAME)$(LIB_EXT) $(RM) $(LIB_NAME)$(LIB_EXT)
	if exist $(LIB_NAME)$(PDB_EXT) $(RM) $(LIB_NAME)$(PDB_EXT)
	

clean:
	if exist *$(OBJ_EXT) $(RM) *$(OBJ_EXT)
	if exist $(LIB_NAME)$(LIB_EXT) $(RM) $(LIB_NAME)$(LIB_EXT)
	if exist $(LIB_NAME)$(PDB_EXT) $(RM) $(LIB_NAME)$(PDB_EXT)
