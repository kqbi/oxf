#*******************************************************************************
# Licensed Materials - Property of IBM
# (c) Copyright IBM Corporation 2008, 2014. All Rights Reserved.
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


CESubsystem=windowsce,6.00
CEVersion=600
CEConfigName=OPPS

CECrtMT=T
CECrtMTDebug=Td
CPP=cl.exe


!IF "$(MACHINE)" == "SH4"
MACHINE_CPP_FLAGS=/Qsh4 /D "SHx" /D "SH4" /D "_SH4_"
MACHINE_FLAG=$(MACHINE)

!ELSEIF "$(MACHINE)" == "MIPS"
MACHINE_CPP_FLAGS=/D "MIPS" /D "_MIPS_"
MACHINE_FLAG=$(MACHINE)

!ELSEIF "$(MACHINE)" == "ARM"
MACHINE_CPP_FLAGS=/D "ARM" /D "_ARM_" /D "THUMBSUPPORT"
MACHINE_FLAG=THUMB

!ELSEIF "$(MACHINE)" == "IX86"
MACHINE_CPP_FLAGS= /D "x86" /D "_i386_" /D "_x86_" /D "i_386_" /D "_X86_"
MACHINE_FLAG=$(MACHINE)

!ELSE
!MESSAGE An invalid MACHINE "$(MACHINE)" is specified.
!MESSAGE Please specify MACHINE= SH4 MIPS ARM OR IX86
!ERROR Exiting
!ENDIF


LIB_DIR=..\lib
LIB_PREFIX=Ce$(CEVersion)$(CPU)


COMPILE_FLAGS=
PDB_FLAGS=

BUILD_SET=Debug
USE_PDB=FALSE
RHAP_FLAGS=


!IF "$(BUILD_SET)" == "Debug"
COMPILE_FLAGS=/Od /D "_DEBUG" /M$(CECrtMTDebug)
LIB_POSTFIX=
!ELSEIF "$(BUILD_SET)" == "Release"
COMPILE_FLAGS=/O2 /D "NDEBUG" /M$(CECrtMT)
LIB_POSTFIX=R
!ELSE
!MESSAGE An invalid BUILD_SET "$(BUILD_SET)" is specified.
!MESSAGE Please specify BUILD_SET=Debug or BUILD_SET=Release
!ERROR Existing
!ENDIF


!IF "$(USE_PDB)" == "TRUE"
PDB_FLAGS=/Zi /Fd"$(LIB_NAME)"
!ENDIF

LIB_CMD=link.exe -lib
LIB_FLAGS=/NOLOGO /SUBSYSTEM:$(CESubsystem) /MACHINE:$(MACHINE_FLAG)


LIB_EXT=.lib
PDB_EXT=.pdb
OBJ_EXT=.obj
CPP_EXT=.cpp
H_EXT=.h







CPPFLAGS= /I . /I .. /I ../osconfig/WIN32
CPPFLAGS=$(CPPFLAGS) /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" 
CPPFLAGS=$(CPPFLAGS) $(MACHINE_CPP_FLAGS) /D "_OM_NO_IOSTREAM" 
CPPFLAGS=$(CPPFLAGS) /D UNDER_CE=$(CEVersion) 
CPPFLAGS=$(CPPFLAGS) /D "UNICODE" /D "_OM_UNICODE_ONLY" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS"
CPPFLAGS=$(CPPFLAGS) /nologo /W3 /EHs-c- /Zl /GS-
CPPFLAGS=$(CPPFLAGS) /D "_AFXDLL"
CPPFLAGS=$(CPPFLAGS) $(COMPILE_FLAGS)
CPPFLAGS=$(CPPFLAGS) $(PDB_FLAGS)
CPPFLAGS=$(CPPFLAGS) $(RHAP_FLAGS)




.DEFAULT : ALL

.PHONY : ALL

!INCLUDE "oxfFiles.list"

SRCS = ntos$(CPP_EXT) \
  OMUnicodeHelper$(CPP_EXT) \
  $(OXF_SRC)

HDRS = ntos$(H_EXT) \
  OMUnicodeHelper$(H_EXT) \
  $(OXF_INC)

OBJS = ntos$(OBJ_EXT) \
  OMUnicodeHelper$(OBJ_EXT) \
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
RHAP_FLAGS=/D _OMINSTRUMENT
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
	@echo Cleanup
	if exist *$(OBJ_EXT) $(RM) *$(OBJ_EXT)
	if exist $(LIB_NAME)$(LIB_EXT) $(RM) $(LIB_NAME)$(LIB_EXT)
	if exist $(LIB_NAME)$(PDB_EXT) $(RM) $(LIB_NAME)$(PDB_EXT)
