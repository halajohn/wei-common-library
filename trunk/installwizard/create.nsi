!include Sections.nsh
!include env_mani.nsh

!define VERSION 1.0.0
Name "WeiCommonLib"
OutFile ".\install.exe"
Caption "WeiCommonLib installation wizard"
InstallDir "$PROGRAMFILES\WeiCommonLib"

ShowInstDetails show
ShowUninstDetails show
XPStyle on

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Variable
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Var WCL_DIR
;;; Var WCL_COLOR_SPACE_CONVERTER_PLUGIN_DIR
;;; Var WCL_SUBSAMPLING_CONVERTER_PLUGIN_DIR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Pages
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PageEx Directory
  DirText "Choose the WeiCommonLib installation directory" "WeiCommonLib Installation Folder"
  DirVar $WCL_DIR
  PageCallbacks wcl_install_dir_pre "" wcl_install_dir_post
PageExEnd

PageEx instfiles
PageExEnd

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Sections
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

InstType "Full"

Section "WeiCommonLib" wcs_section_idx
  SectionIn 1
  ;;; WriteRegStr HKLM "Software\WeiCommonLib" "Installdir" "$WCL_DIR"
  ;;; Push $0
  ;;; StrLen $0 "$WCL_COLOR_SPACE_CONVERTER_PLUGIN_DIR"
  ;;; WriteRegDWORD HKLM "Software\WeiCommonLib" "ColorSpaceConverterPluginRootDirStrLength" $0
  ;;; StrLen $0 "$WCL_SUBSAMPLING_CONVERTER_PLUGIN_DIR"
  ;;; WriteRegDWORD HKLM "Software\WeiCommonLib" "SubSamplingConverterPluginRootDirStrLength" $0
  ;;; Pop $0
  ;;; WriteRegStr HKLM "Software\WeiCommonLib" "ColorSpaceConverterPluginRootDir" "$WCL_COLOR_SPACE_CONVERTER_PLUGIN_DIR"
  ;;; WriteRegStr HKLM "Software\WeiCommonLib" "SubSamplingConverterPluginRootDir" "$WCL_SUBSAMPLING_CONVERTER_PLUGIN_DIR"
  CreateDirectory $WCL_DIR\lib
  SetOutPath $WCL_DIR\lib
  File "..\release\wcl_fmtstr.lib"
  File "..\release\wcl_fslib.lib"
  File "..\release\wcl_lexerlib.lib"
  File "..\release\wcl_mathlib.lib"
  File "..\release\wcl_memory_debugger.lib"
  File "..\release\wcl_curve.lib"
  File "..\release\wcl_colorlib.lib"
  File "..\release\wcl_drawinglib.lib"
  File "..\release\wcl_registry.lib"
  File "..\debug\wcl_fmtstr_d.lib"
  File "..\debug\wcl_fslib_d.lib"
  File "..\debug\wcl_lexerlib_d.lib"
  File "..\debug\wcl_mathlib_d.lib"
  File "..\debug\wcl_memory_debugger_d.lib"
  File "..\debug\wcl_curve_d.lib"
  File "..\debug\wcl_colorlib_d.lib"
  File "..\debug\wcl_drawinglib_d.lib"
  File "..\debug\wcl_registry_d.lib"
  CreateDirectory $WCL_DIR\bin
  SetOutPath $WCL_DIR\bin
  File "..\release\wcl_fmtstr.dll"
  File "..\release\wcl_lexerlib.dll"
  File "..\release\wcl_fslib.dll"
  File "..\release\wcl_mathlib.dll"
  File "..\release\wcl_memory_debugger.dll"
  File "..\release\wcl_curve.dll"
  File "..\release\wcl_colorlib.dll"
  File "..\release\wcl_drawinglib.dll"
  File "..\release\wcl_registry.dll"
  File "..\debug\wcl_fmtstr_d.dll"
  File "..\debug\wcl_lexerlib_d.dll"
  File "..\debug\wcl_fslib_d.dll"
  File "..\debug\wcl_mathlib_d.dll"
  File "..\debug\wcl_memory_debugger_d.dll"
  File "..\debug\wcl_curve_d.dll"
  File "..\debug\wcl_colorlib_d.dll"
  File "..\debug\wcl_drawinglib_d.dll"
  File "..\debug\wcl_registry_d.dll"
  CreateDirectory $WCL_DIR\config
  CreateDirectory $WCL_DIR\config\wcl_colorlib
  SetOutPath $WCL_DIR\config\wcl_colorlib
  File "..\wcl_colorlib\config\color_space_info.txt"
  File "..\wcl_colorlib\config\config.ini"
  CreateDirectory $WCL_DIR\plugin
  CreateDirectory $WCL_DIR\plugin\wcl_colorlib
  CreateDirectory $WCL_DIR\plugin\wcl_colorlib\color_space_converter
  SetOutPath $WCL_DIR\plugin\wcl_colorlib\color_space_converter
  File "..\release\wcl_colorlib_color_space_converter_plugin_cie1931_XYZ_nd.dll"
  File "..\release\wcl_colorlib_color_space_converter_plugin_sRGB_nd.dll"
  File "..\release\wcl_colorlib_color_space_converter_plugin_ITU_R_BT_709_RGB_nd.dll"
  File "..\release\wcl_colorlib_color_space_converter_plugin_ITU_R_BT_709_YPbPr_nd.dll"
  File "..\release\wcl_colorlib_color_space_converter_plugin_ITU_R_BT_709_YCbCr_nd.dll"
  File "..\release\wcl_colorlib_color_space_converter_plugin_SMPTE_170M_RGB_nd.dll"
  File "..\release\wcl_colorlib_color_space_converter_plugin_SMPTE_240M_RGB_nd.dll"
  File "..\release\wcl_colorlib_color_space_converter_plugin_custom_RGB_nd.dll"
  File "..\release\wcl_colorlib_color_space_converter_plugin_custom_YCbCr_nd.dll"
  File "..\release\wcl_colorlib_color_space_converter_plugin_custom_YPbPr_nd.dll"
  File "..\debug\wcl_colorlib_color_space_converter_plugin_cie1931_XYZ_d.dll"
  File "..\debug\wcl_colorlib_color_space_converter_plugin_sRGB_d.dll"  
  File "..\debug\wcl_colorlib_color_space_converter_plugin_ITU_R_BT_709_RGB_d.dll"
  File "..\debug\wcl_colorlib_color_space_converter_plugin_ITU_R_BT_709_YPbPr_d.dll"
  File "..\debug\wcl_colorlib_color_space_converter_plugin_ITU_R_BT_709_YCbCr_d.dll"
  File "..\debug\wcl_colorlib_color_space_converter_plugin_SMPTE_170M_RGB_d.dll"
  File "..\debug\wcl_colorlib_color_space_converter_plugin_SMPTE_240M_RGB_d.dll"
  File "..\debug\wcl_colorlib_color_space_converter_plugin_custom_RGB_d.dll"
  File "..\debug\wcl_colorlib_color_space_converter_plugin_custom_YCbCr_d.dll"
  File "..\debug\wcl_colorlib_color_space_converter_plugin_custom_YPbPr_d.dll"
  CreateDirectory $WCL_DIR\plugin\wcl_colorlib\subsampling_converter
  SetOutPath $WCL_DIR\plugin\wcl_colorlib\subsampling_converter
  File "..\release\wcl_colorlib_subsampling_converter_plugin_mpeg2_yuv420_nd.dll"
  File "..\release\wcl_colorlib_subsampling_converter_plugin_custom_yuv444_nd.dll"
  File "..\debug\wcl_colorlib_subsampling_converter_plugin_mpeg2_yuv420_d.dll"
  File "..\debug\wcl_colorlib_subsampling_converter_plugin_custom_yuv444_d.dll"
  CreateDirectory $WCL_DIR\include
  SetOutPath $WCL_DIR\include
  File "..\wcl_types.hpp"
  CreateDirectory $WCL_DIR\include\wcl_fmtstr
  SetOutPath $WCL_DIR\include\wcl_fmtstr
  File "..\wcl_fmtstr\include\fmtstr.h"
  File "..\wcl_fmtstr\include\fmtstr_func.h"
  CreateDirectory $WCL_DIR\include\wcl_curve
  SetOutPath $WCL_DIR\include\wcl_curve
  File "..\wcl_curve\include\wcl_curve.h"
  CreateDirectory $WCL_DIR\include\wcl_lexerlib
  SetOutPath $WCL_DIR\include\wcl_lexerlib
  File "..\wcl_lexerlib\include\lexerlib.h"
  CreateDirectory $WCL_DIR\include\wcl_fslib
  SetOutPath $WCL_DIR\include\wcl_fslib
  File "..\wcl_fslib\include\filename.h"
  CreateDirectory $WCL_DIR\include\wcl_mathlib
  SetOutPath $WCL_DIR\include\wcl_mathlib
  File "..\wcl_mathlib\include\digit.hpp"
  File "..\wcl_mathlib\include\matrix.hpp"
  CreateDirectory $WCL_DIR\include\wcl_memory_debugger
  SetOutPath $WCL_DIR\include\wcl_memory_debugger
  File "..\wcl_memory_debugger\include\memory_debugger.h"
  CreateDirectory $WCL_DIR\include\wcl_colorlib
  SetOutPath $WCL_DIR\include\wcl_colorlib
  File "..\wcl_colorlib\include\cie_chromaticity_diagram.hpp"
  File "..\wcl_colorlib\include\converter.hpp"
  File "..\wcl_colorlib\include\converter.tcc"
  File "..\wcl_colorlib\include\registry.hpp"
  File "..\wcl_colorlib\include\common.hpp"
  File "..\wcl_colorlib\include\color_space_basic_unit_value.hpp"
  File "..\wcl_colorlib\include\color_space_converter.hpp"
  File "..\wcl_colorlib\include\color_space_converter_plugin.hpp"
  File "..\wcl_colorlib\include\color_space_info.hpp"
  File "..\wcl_colorlib\include\converter_plugin.hpp"
  File "..\wcl_colorlib\include\subsampling_converter.hpp"
  File "..\wcl_colorlib\include\subsampling_converter_plugin.hpp"
  File "..\wcl_colorlib\include\plugin_tree.hpp"
  File "..\wcl_colorlib\include\plugin_tree.tcc"
  File "..\wcl_colorlib\include\plugin_info.hpp"
  File "..\wcl_colorlib\include\spectrum.hpp"
  File "..\wcl_colorlib\include\export.hpp"
  File "..\wcl_colorlib\include\exception.hpp"
  File "..\wcl_colorlib\include\colorlib.hpp"
  CreateDirectory $WCL_DIR\include\wcl_drawinglib
  SetOutPath $WCL_DIR\include\wcl_drawinglib
  File "..\wcl_drawinglib\include\drawinglib.hpp"
  CreateDirectory $WCL_DIR\include\wcl_registry
  SetOutPath $WCL_DIR\include\wcl_registry
  File "..\wcl_registry\include\registry.hpp"
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
  ;;; Push path
  ;;; Push $WCL_DIR\color_space_converter_plugin
  ;;; Call AddToEnvVar
  ;;; Push path
  ;;; Push $WCL_DIR\subsampling_converter_plugin
  ;;; Call AddToEnvVar
  ;;;
  writeUninstaller "$WCL_DIR\uninstall.exe"
  CreateDirectory $SMPROGRAMS\WeiCommonLib
  CreateShortCut "$SMPROGRAMS\WeiCommonLib\uninstall.lnk" "$WCL_DIR\uninstall.exe"
sectionend

section "Uninstall"
  ;;; ReadRegStr $WCL_DIR HKLM Software\WeiCommonLib "Installdir"
  ;;; DeleteRegKey HKLM "Software\WeiCommonLib"
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

Function wcl_install_dir_pre
  Push $0
  StrCpy $WCL_DIR "C:\Program Files\WeiCommonLib\"
  Pop $0
FunctionEnd

Function wcl_install_dir_post
  Push $0
  ;;; StrCpy $WCL_COLOR_SPACE_CONVERTER_PLUGIN_DIR "$WCL_DIRcolor_space_converter_plugin"
  ;;; StrCpy $WCL_SUBSAMPLING_CONVERTER_PLUGIN_DIR "$WCL_DIRsubsampling_converter_plugin"
  Pop $0
FunctionEnd
