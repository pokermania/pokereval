#!/bin/sh

BUILDDIR=$1
MASTERDIR=$2
MODULE=poker-eval

SRCDIR=$BUILDDIR/$MODULE
DISTDIR=$MASTERDIR/$MODULE
rm -fR $DISTDIR
mkdir -p $DISTDIR
HEADERS="\
 include/deck_undef.h\
 include/deck_std.h\
 include/deck_astud.h\
 include/rules_undef.h\
 include/combinations.h\
 include/deck_joker.h\
 include/deck.h\
 include/rules_astud.h\
 include/enumdefs.h\
 include/game_std.h\
 include/pokereval_export.h\
 include/game_astud.h\
 include/enumerate.h\
 include/handval.h\
 include/rules_joker.h\
 include/rules_std.h\
 include/enumord.h\
 include/game_joker.h\
 include/handval_low.h\
 include/evx_defs.h\
 include/poker_defs.h\
 include/inlines/eval_joker.h\
 include/inlines/eval_low27.h\
 include/inlines/eval_joker_low.h\
 include/inlines/evx_inlines.h\
 include/inlines/eval.h\
 include/inlines/evx5.h\
 include/inlines/evx7.h\
 include/inlines/evx_action.h\
 include/inlines/eval_omaha.h\
 include/inlines/eval_joker_low8.h\
 include/inlines/eval_low8.h\
 include/inlines/eval_astud.h\
 include/inlines/eval_type.h\
 include/inlines/eval_low.h"

cd $SRCDIR
rsync -avR $HEADERS $DISTDIR/
rsync -av include/poker_config.h.in $DISTDIR/include/poker_config.h

LIBS=Release/poker-eval.lib
rsync -av $LIBS $DISTDIR/lib/

DOCS="\
 NEWS\
 README\
 TODO\
 AUTHORS\
 WHATS-HERE\
 debian/copyright"
rsync -av $DOCS $DISTDIR/doc/
rsync -av ChangeLog $DISTDIR/doc/changelog

EXAMPLES="\
 examples/fish.vcproj\
 examples/hcmp2.vcproj\
 examples/pokenum.vcproj\
 examples/pokenum.c\
 examples/usedecks.vcproj\
 examples/fish.c\
 examples/eval.c\
 examples/five_card_hands.c\
 examples/hcmp2.c\
 examples/hcmpn.c\
 examples/usedecks.c\
 examples/eval.vcproj\
 examples/seven_card_hands.vcproj\
 examples/hcmpn2.vcproj\
 examples/five_card_hands.vcproj\
 examples/getopt_w32.c\
 examples/getopt_w32.h\
 examples/seven_card_hands.c"
rsync -av $EXAMPLES $DISTDIR/examples/

NSI=poker-eval.nsi
rsync -av $NSI $MASTERDIR

export PATH=$PATH:/cygdrive/c/Program\ Files/NSIS
cd $MASTERDIR
makensis $NSI

rm -f $NSI