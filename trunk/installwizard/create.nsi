!include Sections.nsh
!include env_mani.nsh

!define VERSION 1.0.0
Name "WeiCommonLib"

OutFile ".\install.exe"
InstallDir "$PROGRAMFILES\WeiCommonLib"

ShowInstDetails show
ShowUninstDetails show
XPStyle on

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Variable
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Var WCL_DIR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Pages
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PageEx Directory
  DirText "Choose the WeiCommonLib installation directory" "WeiCommonLib Installation Folder"
  DirVar $WCL_DIR
  PageCallbacks wcs_directory_pre
PageExEnd

PageEx instfiles
PageExEnd

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Sections
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

InstType "Full"

Section "WeiCommonLib" wcs_section_idx
  SectionIn 1
  WriteRegStr HKLM "Software\WeiCommonLib" "Installdir" "$WCL_DIR"
  CreateDirectory $WCL_DIR\lib
  SetOutPath $WCL_DIR\lib
  File "..\release\wcl_fmtstr.lib"
  File "..\release\wcl_fslib.lib"
  File "..\release\wcl_lexerlib.lib"
  File "..\release\wcl_mathlib.lib"
  File "..\release\wcl_memory_debugger.lib"
  File "..\debug\wcl_fmtstr_d.lib"
  File "..\debug\wcl_fslib_d.lib"
  File "..\debug\wcl_lexerlib_d.lib"
  File "..\debug\wcl_mathlib_d.lib"
  File "..\debug\wcl_memory_debugger_d.lib"
  CreateDirectory $WCL_DIR\bin
  SetOutPath $WCL_DIR\bin
  File "..\release\wcl_fmtstr.dll"
  File "..\release\wcl_lexerlib.dll"
  File "..\release\wcl_fslib.dll"
  File "..\release\wcl_mathlib.dll"
  File "..\release\wcl_memory_debugger.dll"
  File "..\debug\wcl_fmtstr_d.dll"
  File "..\debug\wcl_lexerlib_d.dll"
  File "..\debug\wcl_fslib_d.dll"
  File "..\debug\wcl_mathlib_d.dll"
  File "..\debug\wcl_memory_debugger_d.dll"
  CreateDirectory $WCL_DIR\include
  CreateDirectory $WCL_DIR\include\wcl_fmtstr
  SetOutPath $WCL_DIR\include\wcl_fmtstr
  File "..\wcl_fmtstr\include\fmtstr.h"
  File "..\wcl_fmtstr\include\fmtstr_func.h"
  CreateDirectory $WCL_DIR\include\wcl_lexerlib
  SetOutPath $WCL_DIR\include\wcl_lexerlib
  File "..\wcl_lexerlib\include\lexerlib.h"
  CreateDirectory $WCL_DIR\include\wcl_fslib
  SetOutPath $WCL_DIR\include\wcl_fslib
  File "..\wcl_fslib\include\filename.h"
  CreateDirectory $WCL_DIR\include\wcl_mathlib
  SetOutPath $WCL_DIR\include\wcl_mathlib
  File "..\wcl_mathlib\include\math.h"
  CreateDirectory $WCL_DIR\include\wcl_memory_debugger
  SetOutPath $WCL_DIR\include\wcl_memory_debugger
  File "..\wcl_memory_debugger\include\memory_debugger.h"
  CreateDirectory $WCL_DIR\MSVC
  SetOutPath $WCL_DIR\MSVC
  File "..\MSVC\wcl.vsprops"
  File "..\MSVC\wcl_d.vsprops"
  CreateDirectory $SMPROGRAMS\WeiCommonLib
  ;;; Add to environment variable
  Push "WCL_BASEPATH"
  Push $WCL_DIR
  Call AddToEnvVar
  Push path
  Push $WCL_DIR\bin
  Call AddToEnvVar
  ;;;
  writeUninstaller "$WCL_DIR\uninstall.exe"
  CreateDirectory $SMPROGRAMS\WeiCommonLib
  CreateShortCut "$SMPROGRAMS\WeiCommonLib\uninstall.lnk" "$WCL_DIR\uninstall.exe"
sectionend

section "Uninstall"
  ReadRegStr $WCL_DIR HKLM Software\WeiCommonLib "Installdir"
  DeleteRegKey HKLM "Software\WeiCommonLib"
  delete "$WCL_DIR\uninstall.exe"
  delete "$SMPROGRAMS\WeiCommonLib\uninstall.lnk"
  RMDir /r "$WCL_DIR\include\"
  RMDir /r "$WCL_DIR\lib\"
  RMDir /r "$WCL_DIR\bin\"
  RMDir /r "$WCL_DIR\MSVC\"
  RMDir /r "$WCL_DIR\"
  RMDir /r "$SMPROGRAMS\WeiCommonLib\"
  RMDir "$SMPROGRAMS\WeiCommonLib\"
  ;;; remove from path environment variable
  Push "WCL_BASEPATH"
  Push $WCL_DIR
  Call un.RemoveFromEnvVar
  Push "path"  
  Push $WCL_DIR\bin
  Call un.RemoveFromEnvVar
  ;;;
SectionEnd

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Functions
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Function wcs_directory_pre
  Push $0
  StrCpy $WCL_DIR "C:\Program Files\WeiCommonLib\"
  Pop $0
FunctionEnd
