# Microsoft Developer Studio Project File - Name="oxf" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=OXF - WIN32 OXFINST
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "oxf.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "oxf.mak" CFG="OXF - WIN32 OXFINST"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "oxf - Win32 oxfinst" (based on "Win32 (x86) Static Library")
!MESSAGE "oxf - Win32 oxf" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "oxf - Win32 oxfinst"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\oxf___Wi"
# PROP BASE Intermediate_Dir ".\oxf___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\oxfinst"
# PROP Intermediate_Dir ".\oxfinst"
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W4 /GX /Zi /Od /I "../osconfig/WIN32" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_OMINSTRUMENT" /D "_SIM_TIMER" /FR /YX /c
# ADD CPP /nologo /MDd /W4 /GX /ZI /Od /I ".." /I "../osconfig/WIN32" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_OMINSTRUMENT" /FR /Fd".\oxfinst\msoxfinst.pdb" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"oxfsiminst\oxfsiminst.lib"
# ADD LIB32 /nologo /out:".\oxfinst\msoxfinst.lib"
# Begin Special Build Tool
TargetDir=.\oxfinst
TargetName=msoxfinst
SOURCE="$(InputPath)"
PostBuild_Cmds=if exist ..\UPDATELIB. copy $(TargetDir)\$(TargetName).lib     ..\lib 	if exist ..\UPDATELIB. copy $(TargetDir)\$(TargetName).pdb  ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "oxf - Win32 oxf"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\oxf___Wi"
# PROP BASE Intermediate_Dir ".\oxf___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\oxf"
# PROP Intermediate_Dir ".\oxf"
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W4 /GX /Zi /Od /I "../osconfig/WIN32" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_SIM_TIMER" /FR /YX /c
# ADD CPP /nologo /MDd /W4 /GX /ZI /Od /I ".." /I "../osconfig/WIN32" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Fd".\oxf\msoxf.pdb" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"oxfsim\oxfsim.lib"
# ADD LIB32 /nologo /out:".\oxf\msoxf.lib"
# Begin Special Build Tool
TargetDir=.\oxf
TargetName=msoxf
SOURCE="$(InputPath)"
PostBuild_Cmds=if exist ..\UPDATELIB. copy $(TargetDir)\$(TargetName).lib     ..\lib 	if exist ..\UPDATELIB. copy $(TargetDir)\$(TargetName).pdb  ..\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "oxf - Win32 oxfinst"
# Name "oxf - Win32 oxf"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ntos.cpp
# End Source File
# Begin Source File

SOURCE=.\OMAnimReactive.cpp
# End Source File
# Begin Source File

SOURCE=.\OMCore.cpp
# End Source File
# Begin Source File

SOURCE=.\OMDefaultInBound.cpp
# End Source File
# Begin Source File

SOURCE=.\OMDefaultOutBound.cpp
# End Source File
# Begin Source File

SOURCE=.\OMDefaultReactivePort.cpp
# End Source File
# Begin Source File

SOURCE=.\OMDelay.cpp
# End Source File
# Begin Source File

SOURCE=.\OMEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\OMHandleCloser.cpp
# End Source File
# Begin Source File

SOURCE=.\OMMainThread.cpp
# End Source File
# Begin Source File

SOURCE=.\ommemorymanager.cpp
# End Source File
# Begin Source File

SOURCE=.\OMMemoryManagerSwitchHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\OMMemoryManagerSwitchHelperImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\OMMemoryManagerWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\OMNotifier.cpp
# End Source File
# Begin Source File

SOURCE=.\OMOSEventGenerationParams.cpp
# End Source File
# Begin Source File

SOURCE=.\omprotected.cpp
# End Source File
# Begin Source File

SOURCE=.\omreactive.cpp
# End Source File
# Begin Source File

SOURCE=.\omstring.cpp
# End Source File
# Begin Source File

SOURCE=.\omthread.cpp
# End Source File
# Begin Source File

SOURCE=.\OMThreadManager.cpp
# End Source File
# Begin Source File

SOURCE=.\OMTimeout.cpp
# End Source File
# Begin Source File

SOURCE=.\OMTimerManager.cpp
# End Source File
# Begin Source File

SOURCE=.\OMTimerManagerDefaults.cpp
# End Source File
# Begin Source File

SOURCE=.\OMUnicodeHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\os.cpp
# End Source File
# Begin Source File

SOURCE=.\oxf.cpp
# End Source File
# Begin Source File

SOURCE=.\OXFDllGuards.cpp
# End Source File
# Begin Source File

SOURCE=.\OXFEvents.cpp
# End Source File
# Begin Source File

SOURCE=.\OXFRefManager.cpp
# End Source File
# Begin Source File

SOURCE=.\OXFTimeManagement.cpp
# End Source File
# Begin Source File

SOURCE=.\OXFTypeSafeContainers.cpp
# End Source File
# Begin Source File

SOURCE=.\state.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AMemAloc.h
# End Source File
# Begin Source File

SOURCE=.\event.h
# End Source File
# Begin Source File

SOURCE=.\HdlCls.h
# End Source File
# Begin Source File

SOURCE=.\IOxfActive.h
# End Source File
# Begin Source File

SOURCE=.\IOxfAnimReactive.h
# End Source File
# Begin Source File

SOURCE=.\IOxfAnimThreadManager.h
# End Source File
# Begin Source File

SOURCE=.\IOxfAnimTimerManager.h
# End Source File
# Begin Source File

SOURCE=.\IOXFCore.h
# End Source File
# Begin Source File

SOURCE=.\IOxfEvent.h
# End Source File
# Begin Source File

SOURCE=.\IOxfEventGenerationParams.h
# End Source File
# Begin Source File

SOURCE=.\IOxfEventSender.h
# End Source File
# Begin Source File

SOURCE=.\IOxfMemoryAllocator.h
# End Source File
# Begin Source File

SOURCE=.\IOxfReactive.h
# End Source File
# Begin Source File

SOURCE=.\IOxfTickTimerFactory.h
# End Source File
# Begin Source File

SOURCE=.\IOxfTimeout.h
# End Source File
# Begin Source File

SOURCE=.\MemAlloc.h
# End Source File
# Begin Source File

SOURCE=.\OMAbstractContainer.h
# End Source File
# Begin Source File

SOURCE=.\OMAnimReactive.h
# End Source File
# Begin Source File

SOURCE=.\omcollec.h
# End Source File
# Begin Source File

SOURCE=.\OMCore.h
# End Source File
# Begin Source File

SOURCE=.\OMDefaultInBound.h
# End Source File
# Begin Source File

SOURCE=.\OMDefaultOutBound.h
# End Source File
# Begin Source File

SOURCE=.\OMDefaultReactivePort.h
# End Source File
# Begin Source File

SOURCE=.\OMDelay.h
# End Source File
# Begin Source File

SOURCE=.\OMEvent.h
# End Source File
# Begin Source File

SOURCE=.\OMEventQueue.h
# End Source File
# Begin Source File

SOURCE=.\OMHandleCloser.h
# End Source File
# Begin Source File

SOURCE=.\omheap.h
# End Source File
# Begin Source File

SOURCE=.\omiotypes.h
# End Source File
# Begin Source File

SOURCE=.\OMIterator.h
# End Source File
# Begin Source File

SOURCE=.\omlist.h
# End Source File
# Begin Source File

SOURCE=.\OMMainThread.h
# End Source File
# Begin Source File

SOURCE=.\ommap.h
# End Source File
# Begin Source File

SOURCE=.\ommemorymanager.h
# End Source File
# Begin Source File

SOURCE=.\OMMemoryManagerSwitchHelper.h
# End Source File
# Begin Source File

SOURCE=.\OMMemoryManagerSwitchHelperImpl.h
# End Source File
# Begin Source File

SOURCE=.\OMMemoryManagerWrapper.h
# End Source File
# Begin Source File

SOURCE=.\OMNotifier.h
# End Source File
# Begin Source File

SOURCE=.\OMNullValue.h
# End Source File
# Begin Source File

SOURCE=.\OMObsolete.h
# End Source File
# Begin Source File

SOURCE=.\OMOSEventGenerationParams.h
# End Source File
# Begin Source File

SOURCE=.\omoutput.h
# End Source File
# Begin Source File

SOURCE=.\omprotected.h
# End Source File
# Begin Source File

SOURCE=.\omqueue.h
# End Source File
# Begin Source File

SOURCE=.\omreactive.h
# End Source File
# Begin Source File

SOURCE=.\OMResourceGuard.h
# End Source File
# Begin Source File

SOURCE=.\OMSelfLinkedMemoryAllocator.h
# End Source File
# Begin Source File

SOURCE=.\omstack.h
# End Source File
# Begin Source File

SOURCE=.\omstatic.h
# End Source File
# Begin Source File

SOURCE=.\OMStaticArray.h
# End Source File
# Begin Source File

SOURCE=.\omstring.h
# End Source File
# Begin Source File

SOURCE=.\omthread.h
# End Source File
# Begin Source File

SOURCE=.\OMThreadManager.h
# End Source File
# Begin Source File

SOURCE=.\OMTimeout.h
# End Source File
# Begin Source File

SOURCE=.\OMTimerManager.h
# End Source File
# Begin Source File

SOURCE=.\OMTimerManagerDefaults.h
# End Source File
# Begin Source File

SOURCE=.\OMTMMessageQueue.h
# End Source File
# Begin Source File

SOURCE=.\omtypes.h
# End Source File
# Begin Source File

SOURCE=.\OMUAbstractContainer.h
# End Source File
# Begin Source File

SOURCE=.\omucollec.h
# End Source File
# Begin Source File

SOURCE=.\OMUIterator.h
# End Source File
# Begin Source File

SOURCE=.\omulist.h
# End Source File
# Begin Source File

SOURCE=.\omumap.h
# End Source File
# Begin Source File

SOURCE=.\OMUnicodeHelper.h
# End Source File
# Begin Source File

SOURCE=.\OMValueCompare.h
# End Source File
# Begin Source File

SOURCE=.\os.h
# End Source File
# Begin Source File

SOURCE=.\oxf.h
# End Source File
# Begin Source File

SOURCE=.\OXFCogeGen50.h
# End Source File
# Begin Source File

SOURCE=.\OXFDllGuards.h
# End Source File
# Begin Source File

SOURCE=.\OXFEvents.h
# End Source File
# Begin Source File

SOURCE=.\OXFGenMacros.h
# End Source File
# Begin Source File

SOURCE=.\OXFGuardMacros.h
# End Source File
# Begin Source File

SOURCE=.\OXFManager.h
# End Source File
# Begin Source File

SOURCE=.\OXFMemoryManagerMacros.h
# End Source File
# Begin Source File

SOURCE=.\OXFMemoryPoolsMacros.h
# End Source File
# Begin Source File

SOURCE=.\OXFNotifyMacros.h
# End Source File
# Begin Source File

SOURCE=.\OXFPools.h
# End Source File
# Begin Source File

SOURCE=.\OXFPortMacros.h
# End Source File
# Begin Source File

SOURCE=.\OXFRefLock.h
# End Source File
# Begin Source File

SOURCE=.\OXFRefManager.h
# End Source File
# Begin Source File

SOURCE=.\OXFSelectiveInclude.h
# End Source File
# Begin Source File

SOURCE=.\OXFStatechartMacros.h
# End Source File
# Begin Source File

SOURCE=.\OXFSTLMacros.h
# End Source File
# Begin Source File

SOURCE=.\OXFTimeManagement.h
# End Source File
# Begin Source File

SOURCE=.\OXFTypes.h
# End Source File
# Begin Source File

SOURCE=.\OXFTypeSafeContainers.h
# End Source File
# Begin Source File

SOURCE=.\OXFUtilityMacros.h
# End Source File
# Begin Source File

SOURCE=.\rawtypes.h
# End Source File
# Begin Source File

SOURCE=.\rp_framework_dll_definition.h
# End Source File
# Begin Source File

SOURCE=.\timer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
