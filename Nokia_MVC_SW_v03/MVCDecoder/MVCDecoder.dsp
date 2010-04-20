# Microsoft Developer Studio Project File - Name="MVCDecoder" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=MVCDecoder - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MVCDecoder.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MVCDecoder.mak" CFG="MVCDecoder - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MVCDecoder - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "MVCDecoder - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MVCDecoder - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "include/" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "../inc" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "MVCDecoder - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W4 /Gm /GX /ZI /Od /I "include/" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:".\include"

!ENDIF 

# Begin Target

# Name "MVCDecoder - Win32 Release"
# Name "MVCDecoder - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\bitbuffer.c
# End Source File
# Begin Source File

SOURCE=.\src\conversion.c
# End Source File
# Begin Source File

SOURCE=.\src\decoder.c
# End Source File
# Begin Source File

SOURCE=.\src\dpb.c
# End Source File
# Begin Source File

SOURCE=.\src\errorconcealment.c
# End Source File
# Begin Source File

SOURCE=.\src\framebuffer.c
# End Source File
# Begin Source File

SOURCE=.\src\globals.c
# End Source File
# Begin Source File

SOURCE=.\src\intrapred.c
# End Source File
# Begin Source File

SOURCE=.\src\invtransform.c
# End Source File
# Begin Source File

SOURCE=.\src\loopfilter.c
# End Source File
# Begin Source File

SOURCE=.\src\macroblock.c
# End Source File
# Begin Source File

SOURCE=.\src\motcomp.c
# End Source File
# Begin Source File

SOURCE=.\src\nccglob.c
# End Source File
# Begin Source File

SOURCE=.\src\parameterset.c
# End Source File
# Begin Source File

SOURCE=.\src\prederrordec.c
# End Source File
# Begin Source File

SOURCE=.\src\sei.c
# End Source File
# Begin Source File

SOURCE=.\src\sequence.c
# End Source File
# Begin Source File

SOURCE=.\src\slice.c
# End Source File
# Begin Source File

SOURCE=.\src\vld.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\armasmdef.h
# End Source File
# Begin Source File

SOURCE=.\include\avcdecoder.h
# End Source File
# Begin Source File

SOURCE=.\include\bitbuffer.h
# End Source File
# Begin Source File

SOURCE=.\include\clipbuf.h
# End Source File
# Begin Source File

SOURCE=.\include\conversion.h
# End Source File
# Begin Source File

SOURCE=.\include\dpb.h
# End Source File
# Begin Source File

SOURCE=.\include\errorconcealment.h
# End Source File
# Begin Source File

SOURCE=.\include\framebuffer.h
# End Source File
# Begin Source File

SOURCE=.\include\globals.h
# End Source File
# Begin Source File

SOURCE=.\include\intrapred.h
# End Source File
# Begin Source File

SOURCE=.\include\invtransform.h
# End Source File
# Begin Source File

SOURCE=.\include\loopfilter.h
# End Source File
# Begin Source File

SOURCE=.\include\macroblock.h
# End Source File
# Begin Source File

SOURCE=.\include\motcomp.h
# End Source File
# Begin Source File

SOURCE=.\include\nccglob.h
# End Source File
# Begin Source File

SOURCE=.\include\nrctypes.h
# End Source File
# Begin Source File

SOURCE=.\include\parameterset.h
# End Source File
# Begin Source File

SOURCE=.\include\prederrordec.h
# End Source File
# Begin Source File

SOURCE=.\include\sei.h
# End Source File
# Begin Source File

SOURCE=.\include\sequence.h
# End Source File
# Begin Source File

SOURCE=.\include\slice.h
# End Source File
# Begin Source File

SOURCE=.\include\vld.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
