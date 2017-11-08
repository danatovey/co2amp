; Windows Installer for co2amp
; Author: Mikhail Polyanskiy (polyanskiy@bnl.gov)
; Brookhaven National Laboratory, USA

!include "MUI.nsh"

;General
Name "co2amp"
OutFile "co2amp_v.20171108_setup.exe"

;Default install path
InstallDir "$PROGRAMFILES\co2amp"          ;default
InstallDirRegKey HKLM "Software\co2amp" "" ;if previous installation exists (overrides default)


;-------------------------Interface Settings---------------------------

!define MUI_ABORTWARNING
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Header\win.bmp"
!define CO2AMP_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\co2amp"
!define CO2AMP_ROOT_KEY "Applications\co2amp.exe"

;Installer pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
  
;Uninstaller pages
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

;Languages
!insertmacro MUI_LANGUAGE "English"


;-------------------------Installer Sections---------------------------

Section "Section_01" Sec01

  ;Read previous installation path from registry
  ReadRegDWORD $0 HKLM "Software\co2amp" ""

  ;Remove previous installation
  SetShellVarContext all
  RMDir /r $0                                   
  RMDir /r "$SMPROGRAMS\co2amp"
  RMDir /r "$INSTDIR"

  ;Write files to installation directory
  SetOutPath "$INSTDIR\gnuplot"
  File /r "gnuplot\*"
  SetOutPath "$INSTDIR\7-zip"
  File /r "7-zip\*"
  SetOutPath "$INSTDIR\src\co2amp-core"
  File "co2amp-core\*.c"
  File "co2amp-core\*.h"
  File "co2amp-core\*.pro"
  SetOutPath "$INSTDIR\src\co2amp-shell"
  File "co2amp-shell\*.cpp"
  File "co2amp-shell\*.h"
  File "co2amp-shell\*.ui"
  File "co2amp-shell\*.rc"
  File "co2amp-shell\*.qrc"
  File "co2amp-shell\*.pro"
  SetOutPath "$INSTDIR\src\co2amp-shell\images"
  File "co2amp-shell\images\*"
  SetOutPath "$INSTDIR\src\images"
  File "images\*"
  SetOutPath "$INSTDIR\src"
  File "installer.nsi"
  SetOutPath "$INSTDIR\doc"
  File "doc\tex\co2amp.pdf"
  SetOutPath "$INSTDIR\doc\tex"
  File "doc\tex\*.tex"
  File "doc\tex\*.bib"
  SetOutPath "$INSTDIR"
  File "co2amp-core\release\co2amp-core.exe"
  File "co2amp-shell\release\co2amp.exe"
  File "C:\Qt\5.9.2\mingw53_32\bin\libgcc_s_dw2-1.dll"
  File "C:\Qt\5.9.2\mingw53_32\bin\libstdc++-6.dll"
  File "C:\Qt\5.9.2\mingw53_32\bin\libwinpthread-1.dll"
  File "C:\Qt\5.9.2\mingw53_32\bin\Qt5Core.dll"
  File "C:\Qt\5.9.2\mingw53_32\bin\Qt5Gui.dll"
  File "C:\Qt\5.9.2\mingw53_32\bin\Qt5Widgets.dll"
  File "C:\Qt\Tools\mingw530_32\bin\libgomp-1.dll"
  SetOutPath "$INSTDIR\platforms"
  File "C:\Qt\5.9.2\mingw53_32\plugins\platforms\qwindows.dll"
  
  ;Write Start menu entries
  SetShellVarContext all
  CreateDirectory "$SMPROGRAMS\co2amp"
  CreateShortCut "$SMPROGRAMS\co2amp\co2amp.lnk" "$INSTDIR\co2amp.exe"
  ;SetOutPath "$SMPROGRAMS\co2amp"
  ;SetOverwrite on
  ;File "co2amp homepage.url"
  CreateShortCut "$SMPROGRAMS\co2amp\Uninstall co2amp.lnk" "$INSTDIR\uninstall.exe" "" ""
  
  ;Create desktope shortcut
  CreateShortCut "$DESKTOP\co2amp.lnk" "$INSTDIR\co2amp.exe"

  ;Registry
  WriteRegStr HKLM "SOFTWARE\co2amp" "" $INSTDIR
  WriteRegStr HKCR "${CO2AMP_ROOT_KEY}\SupportedTypes" ".co2" ""
  WriteRegStr HKCR "${CO2AMP_ROOT_KEY}\SupportedTypes" ".co2x" ""
  WriteRegStr HKCR "${CO2AMP_ROOT_KEY}\shell\open" "FriendlyAppName" "co2amp"
  WriteRegStr HKCR "${CO2AMP_ROOT_KEY}\shell\open\command" "" '"$INSTDIR\co2amp.exe" "%1$"'
  
  ;Register extensions
  WriteRegStr HKCR ".co2\OpenWithProgIds" "co2amp.co2" ""
  WriteRegStr HKCR "co2amp.co2\shell\open" "FriendlyAppName" "co2amp";
  WriteRegStr HKCR "co2amp.co2\shell\open\command" "" '"$INSTDIR\co2amp.exe" "%1"'
  WriteRegStr HKCR ".co2x\OpenWithProgIds" "co2amp.co2x" ""
  WriteRegStr HKCR "co2amp.co2x\shell\open" "FriendlyAppName" "co2amp";
  WriteRegStr HKCR "co2amp.co2x\shell\open\command" "" '"$INSTDIR\co2amp.exe" "%1"'

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  WriteRegStr HKLM "${CO2AMP_UNINST_KEY}" "UninstallString" "$INSTDIR\uninstall.exe"
  WriteRegStr HKLM "${CO2AMP_UNINST_KEY}" "DisplayName" "co2amp"
  WriteRegStr HKLM "${CO2AMP_UNINST_KEY}" "DisplayIcon" "$INSTDIR\co2amp.exe"

SectionEnd


;-------------------------Uninstaller Section---------------------------

Section "Uninstall"

  SetShellVarContext all
  RMDir /r "$SMPROGRAMS\co2amp"
  Delete "$DESKTOP\co2amp.lnk"

  Delete "$INSTDIR\uninstall.exe"
  RMDir /r "$INSTDIR"

  ;unregister extensions
  DeleteRegKey HKLM "Software\co2amp"
  DeleteRegKey HKLM "${CO2AMP_UNINST_KEY}"
  DeleteRegKey HKCR "${CO2AMP_ROOT_KEY}"
  DeleteRegValue HKCR ".co2\OpenWithProgIds" "co2amp.co2"
  DeleteRegValue HKCR ".co2x\OpenWithProgIds" "co2amp.co2x"
  DeleteRegKey HKCR "co2amp.co2"
  DeleteRegKey HKCR "co2amp.co2x"

SectionEnd
