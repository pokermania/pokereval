; poker-eval.nsi
; based on
; example1.nsi
;
; This script is perhaps one of the simplest NSIs you can make. All of the
; optional settings are left to their default settings. The installer simply 
; prompts the user asking them where to install, and drops a copy of makensisw.exe
; there. 

;--------------------------------

; The name of the installer
Name "poker-eval"

; The file to write
OutFile "poker-eval.exe"

; The default installation directory
InstallDir $PROGRAMFILES\poker-eval

;--------------------------------

; Pages

Page directory
Page instfiles

;--------------------------------

; The stuff to install
Section "" ;No components page, name is not important

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  CreateDirectory $INSTDIR\examples
  FILE /oname=$INSTDIR\examples\hcmpn.c examples\hcmpn.c 
  FILE /oname=$INSTDIR\examples\hcmpn2.vcproj examples\hcmpn2.vcproj 
  FILE /oname=$INSTDIR\examples\eval.c examples\eval.c
  FILE /oname=$INSTDIR\examples\eval.vcproj examples\eval.vcproj
  FILE /oname=$INSTDIR\examples\fish.c examples\fish.c
  FILE /oname=$INSTDIR\examples\fish.vcproj examples\fish.vcproj
  FILE /oname=$INSTDIR\examples\five_card_hands.c examples\five_card_hands.c
  FILE /oname=$INSTDIR\examples\five_card_hands.vcproj examples\five_card_hands.vcproj
  FILE /oname=$INSTDIR\examples\hcmp2.c examples\hcmp2.c
  FILE /oname=$INSTDIR\examples\hcmp2.vcproj examples\hcmp2.vcproj
  FILE /oname=$INSTDIR\examples\seven_card_hands.c examples\seven_card_hands.c
  FILE /oname=$INSTDIR\examples\seven_card_hands.vcproj examples\seven_card_hands.vcproj
  FILE /oname=$INSTDIR\examples\pokenum.c examples\pokenum.c
  FILE /oname=$INSTDIR\examples\pokenum.vcproj examples\pokenum.vcproj
  FILE /oname=$INSTDIR\examples\usedecks.c examples\usedecks.c
  FILE /oname=$INSTDIR\examples\usedecks.vcproj examples\usedecks.vcproj
  FILE /oname=$INSTDIR\examples\getopt_w32.c examples\getopt_w32.c
  FILE /oname=$INSTDIR\examples\getopt_w32.h examples\getopt_w32.h
  CreateDirectory $INSTDIR\doc
  File /oname=$INSTDIR\doc\NEWS NEWS
  File /oname=$INSTDIR\doc\README README
  File /oname=$INSTDIR\doc\TODO TODO
  File /oname=$INSTDIR\doc\AUTHORS AUTHORS
  File /oname=$INSTDIR\doc\WHATS-HERE WHATS-HERE
  File /oname=$INSTDIR\doc\copyright debian\copyright
  File /oname=$INSTDIR\doc\changelog ChangeLog

  CreateDirectory $INSTDIR\lib
  File /oname=$INSTDIR\lib\poker-eval.lib Release\poker-eval.lib
  CreateDirectory $INSTDIR\include
  CreateDirectory $INSTDIR\include\inlines
  File /oname=$INSTDIR\include\inlines\eval.h include\inlines\eval.h
  File /oname=$INSTDIR\include\inlines\eval_astud.h include\inlines\eval_astud.h
  File /oname=$INSTDIR\include\inlines\eval_joker.h include\inlines\eval_joker.h
  File /oname=$INSTDIR\include\inlines\eval_joker_low.h include\inlines\eval_joker_low.h
  File /oname=$INSTDIR\include\inlines\eval_joker_low8.h include\inlines\eval_joker_low8.h
  File /oname=$INSTDIR\include\inlines\eval_low.h include\inlines\eval_low.h
  File /oname=$INSTDIR\include\inlines\eval_low8.h include\inlines\eval_low8.h
  File /oname=$INSTDIR\include\inlines\eval_low27.h include\inlines\eval_low27.h
  File /oname=$INSTDIR\include\inlines\eval_omaha.h include\inlines\eval_omaha.h
  File /oname=$INSTDIR\include\inlines\eval_type.h include\inlines\eval_type.h
  File /oname=$INSTDIR\include\inlines\evx5.h include\inlines\evx5.h
  File /oname=$INSTDIR\include\inlines\evx7.h include\inlines\evx7.h
  File /oname=$INSTDIR\include\inlines\evx_action.h include\inlines\evx_action.h
  File /oname=$INSTDIR\include\inlines\evx_inlines.h include\inlines\evx_inlines.h
  File /oname=$INSTDIR\include\combinations.h include\combinations.h
  File /oname=$INSTDIR\include\deck.h include\deck.h
  File /oname=$INSTDIR\include\deck_astud.h include\deck_astud.h
  File /oname=$INSTDIR\include\deck_joker.h include\deck_joker.h
  File /oname=$INSTDIR\include\deck_std.h include\deck_std.h
  File /oname=$INSTDIR\include\deck_undef.h include\deck_undef.h
  File /oname=$INSTDIR\include\enumdefs.h include\enumdefs.h
  File /oname=$INSTDIR\include\enumerate.h include\enumerate.h
  File /oname=$INSTDIR\include\enumord.h include\enumord.h
  File /oname=$INSTDIR\include\evx_defs.h include\evx_defs.h
  File /oname=$INSTDIR\include\game_astud.h include\game_astud.h
  File /oname=$INSTDIR\include\game_joker.h include\game_joker.h
  File /oname=$INSTDIR\include\game_std.h include\game_std.h
  File /oname=$INSTDIR\include\handval.h include\handval.h
  File /oname=$INSTDIR\include\handval_low.h include\handval_low.h
  File /oname=$INSTDIR\include\poker_config.h include\poker_config.h.in
  File /oname=$INSTDIR\include\poker_defs.h include\poker_defs.h
  File /oname=$INSTDIR\include\pokereval_export.h include\pokereval_export.h
  File /oname=$INSTDIR\include\rules_astud.h include\rules_astud.h
  File /oname=$INSTDIR\include\rules_joker.h include\rules_joker.h
  File /oname=$INSTDIR\include\rules_std.h include\rules_std.h
  File /oname=$INSTDIR\include\rules_undef.h include\rules_undef.h  

SectionEnd ; end the section