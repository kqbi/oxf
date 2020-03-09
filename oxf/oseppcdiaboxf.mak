#*******************************************************************************
# Licensed Materials - Property of IBM
# (c) Copyright IBM Corporation 2008, 2014. All Rights Reserved.
#
# Note to U.S. Government Users Restricted Rights:  
# Use, duplication or disclosure restricted by GSA ADP Schedule 
# Contract with IBM Corp.
#*******************************************************************************
BOARD *= MOTOROLA_FADS860T

# Tools-win32 (WinNT/95 command line commands)
SILENT           = @
ECHO             = $(SILENT)+echo
#RM              = del
#.IF "$(OS)" == "Windows_NT"
#RM              = del /q
#.END
CP               = copy
MKDIR            = mkdir

###############################################################################
# DIAB COMPILER AND OSE ROOT PATHS
###############################################################################

.IMPORT .IGNORE : OSE_ROOT
OSEROOT = $(OSE_ROOT)

all:
.IF "$(OSEROOT)" == ""
	@+$(ECHO) "========================================================" $(ECHOEND)
	@+$(ECHO) Environment variable OSE_ROOT is not defined $(ECHOEND)
	@+$(ECHO) "========================================================" $(ECHOEND)
.END

$(eq,"$(OSEROOT)","" .EXIT: .IGNORE: )


.IMPORT .IGNORE : DIAB_ROOT
DIABROOT = $(DIAB_ROOT)

checkDiabRoot:
.IF "$(DIAB_ROOT)" == ""
	@+$(ECHO) "========================================================" $(ECHOEND)
	@+$(ECHO) Environment variable DIAB_ROOT MUST be defined $(ECHOEND)
	@+$(ECHO) "========================================================" $(ECHOEND)
.ELSE
	@+$(ECHO) Using environment variable DIAB_ROOT=$(DIAB_ROOT) $(ECHOEND)
.END

$(eq,"$(DIABROOT)","" .EXIT: .IGNORE: )


EXAMPLES_COMMON         *= $(OSEROOT)$/examples$/common
EXAMPLES_COMMON_CONF 	*= $(EXAMPLES_COMMON)$/conf
EXAMPLES_COMMON_INCLUDE *= $(EXAMPLES_COMMON)$/include
EXAMPLES_COMMON_MAKE 	*= $(EXAMPLES_COMMON)$/make
EXAMPLES_COMMON_SRC 	*= $(EXAMPLES_COMMON)$/src

# Inclusion of your common settings.
# In this file, you can enter constants to be used for all
# examples, e.g. COMPILER, COMPILERROOT etc.
include $(EXAMPLES_COMMON_MAKE)$/common_settings.mk 
include $(EXAMPLES_COMMON_MAKE)$/select_cpu_and_bsp.mk

.IF $(HOST) == UNIX 
  include $(EXAMPLES_COMMON_MAKE)$/tools-unix.mk
.ELSE
  include $(EXAMPLES_COMMON_MAKE)$/tools-win32.mk
.END



###############################################################################
# SUFFIXES
###############################################################################

targets=oxf oxfinst


.DEFAULT : all
.SUFFIXES: .cpp .c .o
#.PHONY : all
#.ERROR : clean


CONF=$(DIABROOT)\conf\dtools.conf
###############################################################################
# DIAB COMPILER CONFIGURATION, FLAGS, DEFINES AND INCLUDE PATHS
###############################################################################

# DIAB compiler, assembler, and linker
DIABBIN		 = $(DIABROOT)\win32\bin
PREPROCESSOR	 = $(DIABBIN)\dcc.exe -E 
CC		 = $(DIABBIN)\dcc.exe
CPP		 = $(DIABBIN)\dplus.exe
ASM		 = $(DIABBIN)\das.exe 
LD		 = $(DIABBIN)\dld.exe
DDUMP		 = $(DIABBIN)\ddump.exe -Rv
DAR		 = $(DIABBIN)\dar.exe -ru


# Common macro definitions, DO NOT TOUCH !
LIB_DIR		 = ..$/lib
LIB_PREFIX	 = OSE
LIB_POSTFIX	 = PPC$(PROCESSOR)

# Flags used later in this makefile
STL_FLAGS	 =
COMPILE_FLAGS	 =
RHAP_FLAGS	 =

USE_STL		 = FLASE

# Release or Debug build set
BUILD_SET	 =
.IF "$(BUILD_SET)" == "DEBUG"
COMPILE_FLAGS	 = -DOS_DEBUG
.ELIF "$(BUILD_SET)" == "RELEASE"
COMPILE_FLAGS	 =
.END


# File extensions
LIB_EXT		 = .a
OBJ_EXT		 = .o
CPP_EXT		 = .cpp
H_EXT		 = .h

# Include paths
INCLUDE		 = -I. -I.. -I../osconfig/OSE -I$(OSEROOT)\powerpc\krn-403\include
INCLUDE		+= -I$(OSEROOT)\powerpc\include

# Flags for CPP compiler
CPPFLAGS	 = -c -DOM_NO_RCS_ID

.IF "$(BUILD_SET)" == "DEBUG"
CPPFLAGS	+= -g
.END

CPPFLAGS	+= -Xansi -Xforce-declarations -Xforce-prototypes -D__DIAB
CPPFLAGS	+= -Xsmall-data=0 -Xsmall-const=0 
CPPFLAGS	+= $(INCLUDE)
CPPFLAGS	+= $(COMPILE_FLAGS)
CPPFLAGS	+= $(STL_FLAGS)
CPPFLAGS	+= $(RHAP_FLAGS)



# Flags for C compiler (sig.c)
CFLAGS		 = -c

.IF "$(BUILD_SET)" == "DEBUG"
CPPFLAGS	+= -g
.END
 
CFLAGS		+= -Xansi -Xforce-declarations -Xforce-prototypes -D__DIAB
CFLAGS		+= $(INCLUDE)
CFLAGS		+= $(COMPILE_FLAGS)
CFLAGS		+= $(STL_FLAGS)
CFLAGS		+= $(RHAP_FLAGS)

include oxfFiles.list

###############################################################################
# SOURCE FILES
###############################################################################

SRCS = oseOS$(CPP_EXT) \
  osesocket$(CPP_EXT) \
  sig.c \
  $(OXF_SRC)

###############################################################################
# HEADER FILES
###############################################################################

HDRS = oseOS$(H_EXT) \
  osesocket$(H_EXT) \
  $(OXF_INC)

###############################################################################
# OBJECT FILES TO BE COMPILE
###############################################################################

OBJS = oseOS$(OBJ_EXT) \
  osesocket$(OBJ_EXT) \
  sig$(OBJ_EXT) \
  $(OXF_OBJ)


LIB_NAME=$(LIB_PREFIX)$(TARGET_NAME)$(LIB_POSTFIX)

.IF "$(CFG)" == "oxf"
TARGET_NAME      = oxf
RHAP_FLAGS       =
COMPILE_FLAGS   += -DOSE_DELTA -D_REENTRANT -DBIG_ENDIAN 
all: $(LIB_DIR)$/$(LIB_NAME)$(LIB_EXT)

.ELIF "$(CFG)" == "oxfinst"
TARGET_NAME      = oxfinst
RHAP_FLAGS       = -D_OMINSTRUMENT 
COMPILE_FLAGS   += -DOSE_DELTA -D_REENTRANT -DBIG_ENDIAN -DUSE_IOSTREAM
all: $(LIB_DIR)$/$(LIB_NAME)$(LIB_EXT)

.ELSE
all:
	$(ECHO) Usage: $(MAKE) all "CFG=<target>". $(ECHOEND)
	$(ECHO) where target is one of $(targets) $(ECHOEND)

.END

###############################################################################
# TARGETS
###############################################################################
# Creating library files

$(LIB_DIR)$/$(LIB_NAME)$(LIB_EXT) : checkDiabRoot $(LIB_DIR) $(OBJS)
	$(ECHO) Creating $@ library file $(ECHOEND)
	$(SILENT)$(DAR) $@ $(OBJS)
	$(SILENT)$(RM) "*$(OBJ_EXT)"

###############################################################################
# CREATE LIB DIRECTORY
###############################################################################

$(LIB_DIR) :
	@+$(MKDIR) $(LIB_DIR)

###############################################################################
# COMPILE RULES
###############################################################################

%.o : %.c
	$(ECHO) Compiling $< $(ECHOEND)
	$(SILENT)$(CC) $(CFLAGS) $< -o $@

%.o : %.cpp
	$(ECHO) Compiling $< $(ECHOEND)
	$(SILENT)$(CPP) $(CPPFLAGS) $< -o $@

clean:
	$(ECHO) Cleanup $(ECHOEND)
	$(SILENT)$(RM) $(OBJS) 


###############################################################################
# END OF THIS MAKEFILE
###############################################################################
