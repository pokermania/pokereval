/*
 *  cmpN.c: a program to compare N pairs of hold'em hole cards at any
 *              point of the game (pre-flop, on the flop, turn or river).
 *          now expanded to omaha hi/lo8, 7stud, 7stud hi/lo8, lowball
 *              
 *  Example:
 *
 *      cmpN -h  Tc Ac  3h Ah  9c 9h  --  8c 6h 7h
 *      903 boards containing 7h 6h 8c
 *       cards     win   %win       lose  %lose        tie   %tie
 *      Ac Tc      129  14.29        770  85.27          4   0.44
 *      Ah 3h      311  34.44        588  65.12          4   0.44
 *      9h 9c      459  50.83        440  48.73          4   0.44
 *
 *  Options available:
 *     -h     holdem high evaluation (default)
 *     -h8    holdem hi/lo8 evaluation
 *     -o     omaha hi/lo8 evaluation
 *     -ohi   omaha hi only evaluation
 *     -s     7-stud evaluation (use -- between players)
 *     -s8    7-stud hi/lo8 evaluation (use -- between players)
 *     -l     5 stud ace-to-5 low draw with joker (use -- between players)
 *              can specify discards after a single '-', e.g.
 *                -l Ac 3c 5s 7h - Kd -- 2s 3d 5h 6d 8h
 *              specifies a 1-card draw to a 75 vs. a pat 86.
 *              Use 'X' for the joker.
 *
 *  by Michael Maurer, Feb 1995
 *  Based on cmp2.c, which is Copyright (C) 1993, 1994  Clifford T. Matthews
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <stdlib.h>

#include "poker.h"
#include "eval.h"
#include "mmpoker.h"


PRIVATE char * sprintf_rank(char *buf, uint32 ranks, char suitchar)
{
    int bit;
    const char *namep;
    static char names[] = "AKQJT98765432";

    for (bit = 1 << ace, namep = names; bit; bit >>= 1, ++namep) {
        if (ranks & bit) {
           *buf++ = *namep;
           *buf++ = suitchar;
           *buf++ = ' ';
        }
    }
    return buf;
}

PRIVATE void mydump_uint64(char *buf, uint64 hand)
{
   cards_u cards = uint64_to_cards(hand);
   if (buf) {
      buf = sprintf_rank(buf, cards.cards_t.spades,   's');
      buf = sprintf_rank(buf, cards.cards_t.hearts,   'h');
      buf = sprintf_rank(buf, cards.cards_t.diamonds, 'd');
      buf = sprintf_rank(buf, cards.cards_t.clubs,    'c');
      if (hand & joker64)
         *buf++ = 'X', *buf++ = ' ', *buf++ = ' ';
      *buf = '\0';
   } else {
      char mybuf[128], *p=mybuf;
      memset(mybuf,0,sizeof(mybuf));
      p = sprintf_rank(p, cards.cards_t.spades,   's');
      p = sprintf_rank(p, cards.cards_t.hearts,   'h');
      p = sprintf_rank(p, cards.cards_t.diamonds, 'd');
      p = sprintf_rank(p, cards.cards_t.clubs,    'c');
      if (hand & joker64)
         *p++ = 'X', *p++ = ' ', *p++ = ' ';
      *p = '\0';
      fputs(mybuf,stdout);
   }
}

#define MAXHANDS 23
typedef enum {HOLE, DISCARD, BOARD} state_t;
#define MAXDECK 53

/* START_NESTED_LOOP_COMB and END_NESTED_LOOP_COMB are macros to help us
iterate over m-card subsets from an N-card deck.  The N-card deck is
specified by the bit pattern in bitpat_arg; m is specified by depth_arg.
See examples in cmpN().  Each distinct subset (ignoring order) will be
visited once.  To visit each ordered subset (all permutations of each
combination), use *_NESTED_LOOP_PERM instead. */

#define START_NESTED_LOOP_COMB(depth_arg, bitpat_arg) \
{\
   uint64 bits[MAXDECK+1], ormask[MAXDECK+1];\
   uint64 bit, bitpat;\
   uint8 idx[MAXDECK+1];\
   uint8 j,nbits,depth;\
\
   depth = depth_arg;\
   bitpat = bitpat_arg;\
   for (bit=(uint64)1<<(MAXDECK-1), nbits=0; bit; bit>>=1) {\
      if (bit & bitpat)\
         bits[++nbits] = bit;\
   }\
   if (nbits<depth) {\
      printf("ERROR: Not enough cards\n");\
      return 2;\
   }\
   ormask[0] = 0;\
   for (j=1; j<=depth; j++) {\
      idx[j] = j;\
      ormask[j] = ormask[j-1] | bits[idx[j]];\
   }\
\
   for (;;) {

#define END_NESTED_LOOP_COMB \
      for (j=depth; j>0; j--) {\
         if (idx[j] < nbits-depth+j)\
            break;\
      }\
      if (j==0)\
         break;\
      idx[j]++;\
      ormask[j] = ormask[j-1] | bits[idx[j]];\
      for (j++; j<=depth; j++) {\
         idx[j] = idx[j-1] + 1;\
         ormask[j] = ormask[j-1] | bits[idx[j]];\
      }\
   }\
}

#define START_NESTED_LOOP_PERM(a,b) START_NESTED_LOOP_COMB(a,b)

#define END_NESTED_LOOP_PERM \
      for (j=depth; j>0; j--) {\
         if (bitpat & ~ormask[j-1] & (bits[idx[j]]-1))\
            break;\
      }\
      if (j==0)\
         break;\
      while (bits[++idx[j]] & ormask[j-1]);\
/*      printf("\tmoving elem %d to slot %d\n", j, idx[j]);*/\
      ormask[j] = ormask[j-1] | bits[idx[j]];\
      for (j++; j<=depth; j++) {\
         idx[j] = 0;\
         while (bits[++idx[j]] & ormask[j-1]);\
/*         printf("\t\tstarting elem %d at slot %d\n", j, idx[j]);*/\
         ormask[j] = ormask[j-1] | bits[idx[j]];\
      }\
   }\
}

#define START_NESTED_LOOP_REPLACE(a,b) START_NESTED_LOOP_COMB(a,b)

#define END_NESTED_LOOP_REPLACE \
      do {\
         for (j=depth; j>0; j--) {\
            if (idx[j] == depth)\
               break;\
         }\
         if (j==0)\
            break;\
         idx[j]++;\
         for (j++; j<=depth; j++) {\
            idx[j] = 0;\
         }\
      } while ();\
   }\
}


#define INNER_LOOP_HI(cmd1, cmd2, cmd3) \
   best = 0;\
   for (i=0; i<nplayers; i++) {\
      cmd1;\
      cmd2;\
      cmd3;\
      if (val[i] > best)\
         best = val[i];\
   }\
   nbest = 0;\
   for (i=0; i<nplayers; i++) {\
      if (val[i]==best)\
         nbest++;\
   }\
   hishare = 1.0/nbest;\
   for (i=0; i<nplayers; i++) {\
      if (val[i]==best) {\
         ev[i] += hishare;\
         if (nbest==1)\
            nwin[i]++;\
         else\
            ntie[i]++;\
      }\
   }\
   nhands++;

#define INNER_LOOP_HILO8(cmd1, cmd2, cmd3) \
/*mydump_uint64(NULL,ormask[1]);*/\
/*mydump_uint64(NULL,ormask[2] & ~ormask[1]);*/\
/*mydump_uint64(NULL,ormask[3] & ~ormask[2]);*/\
   best = 0;\
   LObest = 0xffffffff;\
   for (i=0; i<nplayers; i++) {\
      cmd1;\
      cmd2;\
      cmd3;\
      if (val[i] > best)\
         best = val[i];\
      if (LOval[i] < LObest)\
         LObest = LOval[i];\
   }\
   nbest = 0;\
   LOnbest = 0;\
   for (i=0; i<nplayers; i++) {\
      if (val[i]==best)\
         nbest++;\
      if (LOval[i]==LObest)\
         LOnbest++;\
   }\
   hishare = (LObest<=LOqual) ? 0.5 : 1;\
   if (nbest) hishare /= nbest;\
   loshare = 0.5;\
   if (LOnbest) loshare /= LOnbest;\
   for (i=0; i<nplayers; i++) {\
      if (val[i]==best) {\
/*printf("HI:%d ",i);*/\
         ev[i] += hishare;\
         if (nbest==1)\
            nwin[i]++;\
         else\
            ntie[i]++;\
         if (nbest==1 && LObest>LOqual)\
            nscoop[i]++;\
      }\
      if (LOval[i]<=LOqual) {\
         if (LOval[i]==LObest) {\
/*printf("LO:%d ",i);*/\
            ev[i] += loshare;\
            if (LOnbest==1)\
               LOnwin[i]++;\
            else\
               LOntie[i]++;\
            if (val[i]==best && nbest==1 && LOnbest==1)\
               nscoop[i]++;\
         } else\
            LOnlose[i]++;\
      }\
   }\
/*printf("\n");*/\
   nhands++;

#define INNER_LOOP_LO(cmd1, cmd2, cmd3) \
   LObest = 0xffffffff;\
   for (i=0; i<nplayers; i++) {\
      cmd1;\
      cmd2;\
      cmd3;\
      if (LOval[i] < LObest)\
         LObest = LOval[i];\
   }\
   LOnbest = 0;\
   for (i=0; i<nplayers; i++) {\
      if (LOval[i]==LObest)\
         LOnbest++;\
   }\
   loshare = 1.0/LOnbest;\
   for (i=0; i<nplayers; i++) {\
      if (LOval[i]==LObest) {\
         ev[i] += loshare;\
         if (LOnbest==1)\
            LOnwin[i]++;\
         else\
            LOntie[i]++;\
      }\
   }\
   nhands++;

PRIVATE int cmpN(int argc, char *argv[])
{
   uint8 i, k, nplayers, nboard, nbest, LOnbest, dum;
   int ndeal, nhole[MAXHANDS];
   uint64 hole[MAXHANDS], discard[MAXHANDS];
   uint64 board, dead, deck, live, card, common;
   uint32 nhands, best, LObest;
   uint32 val[MAXHANDS], nwin[MAXHANDS], ntie[MAXHANDS], nscoop[MAXHANDS];
   uint32 LOval[MAXHANDS], LOnwin[MAXHANDS], LOntie[MAXHANDS], LOnlose[MAXHANDS];
   uint32 LOqual = ROUGH_EIGHT;                         /* 8 qualifier for low */
   float ev[MAXHANDS], hishare, loshare;
   state_t state;
   game_t game = game_holdem;
   char buf[64];

   for (i=0; i<MAXHANDS; i++) {
      hole[i] = discard[i] = 0;
      nwin[i] = ntie[i] = nscoop[i] = nhole[i] = 0;
      LOnwin[i] = LOntie[i] = LOnlose[i] = 0;
      ev[i] = 0;
   }
   board = dead = 0;
   nplayers = nboard = 0;
   state = HOLE;
   for (i=1; i<argc; i++) {
      card = string_to_card(argv[i]);
      if (!card && *argv[i] == 'X')                     /* joker */
         card = joker64;
      if (!card && *argv[i] != '-') {
         printf("ERROR: Malformed card \"%s\"\n", argv[i]);
         return 1;
      }
      if (!strcmp(argv[i], "-h")) {
         game = game_holdem;
         continue;
      }
      if (!strcmp(argv[i], "-h8")) {
         game = game_holdem8;
         continue;
      }
      if (!strcmp(argv[i], "-o")) {
         game = game_omaha8;
         continue;
      }
      if (!strcmp(argv[i], "-ohi")) {
         game = game_omaha;
         continue;
      }
      if (!strcmp(argv[i], "-s")) {
         game = game_7stud;
         continue;
      }
      if (!strcmp(argv[i], "-s8")) {
         game = game_7stud8;
         continue;
      }
      if (!strcmp(argv[i], "-l")) {
         game = game_lowball;
         continue;
      }
      if (*argv[i] == '-' && strcmp(argv[i],"--") && strcmp(argv[i],"-")) {
         printf("ERROR: Unknown option \"%s\"\n", argv[i]);
         return 1;
      }
      switch (state) {
       case HOLE:
       case DISCARD:
         if (!strcmp(argv[i],"--")) {
            if (game_params[game].maxboard > 0)
               state = BOARD;
            else {
               state = HOLE;
               nplayers++;
            }
         } else if (!strcmp(argv[i],"-")) {
            if (game_params[game].maxboard > 0)
               state = BOARD;
            else
               state = DISCARD;
         } else {
            if (state == HOLE) {
               hole[nplayers] |= card;
               nhole[nplayers]++;
               if (nhole[nplayers] == game_params[game].maxhole &&
                   game_params[game].maxboard > 0)
                  nplayers++;
            } else
               discard[nplayers] |= card;
         }
         break;
       case BOARD:
         board |= card;
         nboard++;
         break;
      }
      dead |= card;
/*      printf("parsed %s, nplayers=%d\n", argv[i], nplayers);*/
   }
   if (hole[nplayers] || discard[nplayers])             /* fix for null board */
      nplayers++;
   for (i=0; i<nplayers; i++) {
      if (game_params[game].maxboard > 0 &&
          nhole[i] < game_params[game].maxhole) {
         printf("ERROR: Wrong number of hole cards\n");
         return 1;
      }
   }
   deck = ~(~(uint64)0 << game_params[game].decksize);
   live = ~dead & deck;
   
#if 0
   for (i=0; i<nplayers; i++) {
      printf("\nplayer %d: ", i);
      mydump_uint64(NULL,hole[i]);
      if (discard[i]) {
         printf("/ ");
         mydump_uint64(NULL,discard[i]);
      }
   }
   printf("\nboard: ");
   mydump_uint64(NULL,board);
   printf("\ndeck: ");
   mydump_uint64(NULL,live);
   printf("\n");
#endif

   nhands = 0;
   switch (game) {
    case game_holdem: {
       ndeal = game_params[game].maxboard - nboard;
       START_NESTED_LOOP_COMB(ndeal,live) {
          common = ormask[depth] | board;
          INNER_LOOP_HI(val[i] = eval(uint64_to_cards(hole[i] | common)),
                        dum=2, dum=3);
       } END_NESTED_LOOP_COMB;
    } break;
    case game_omaha: {
       ndeal = game_params[game].maxboard - nboard;
       START_NESTED_LOOP_COMB(ndeal,live) {
          common = ormask[depth] | board;
          INNER_LOOP_HI((val[i] = eval_omaha(uint64_to_cards(hole[i]),
                                             uint64_to_cards(common))),
                        dum=2,dum=3);
       } END_NESTED_LOOP_COMB;
    } break;
    case game_omaha8: {
       ndeal = game_params[game].maxboard - nboard;
       START_NESTED_LOOP_COMB(ndeal,live) {
          common = ormask[depth] | board;
          INNER_LOOP_HILO8((eval_omaha_hilo(uint64_to_cards(hole[i]),
                                            uint64_to_cards(common),
                                            &val[i], &LOval[i])),
                           dum=2,dum=3);
       } END_NESTED_LOOP_COMB;
    } break;
    case game_holdem8: {
       ndeal = game_params[game].maxboard - nboard;
       START_NESTED_LOOP_COMB(ndeal,live) {
          common = ormask[depth] | board;
          INNER_LOOP_HILO8(cards_u hand = uint64_to_cards(hole[i] | common),
                           val[i] = eval(hand),
                           LOval[i] = eval_lowball5(hand));
       } END_NESTED_LOOP_COMB;
    } break;
    case game_7stud: {
       uint8 start[MAXHANDS], end[MAXHANDS];
       for (ndeal=i=0; i<nplayers; i++) {
          start[i] = ndeal;
          ndeal += game_params[game].maxhole - nhole[i];
          end[i] = ndeal;
       }
       START_NESTED_LOOP_PERM(ndeal,live) {
          INNER_LOOP_HI(uint64 hand = hole[i] | (ormask[end[i]] & ~ormask[start[i]]),
                        val[i] = eval(uint64_to_cards(hand)),
                        dum=3);
       } END_NESTED_LOOP_PERM;
    } break;
    case game_7stud8: {
#if 0
       live = 0x00ff;
       ndeal = 3;
       START_NESTED_LOOP_PERM(ndeal,live) {
          for (i=1; i<=nbits; i++) {
             for (k=ndeal; k>0; k--)
                if (idx[k]==i)
                   break;
             printf("%1d", k);
          }
          nhands++;
       } END_NESTED_LOOP_PERM;
#else
       uint8 start[MAXHANDS], end[MAXHANDS], nc, waste=1;
       for (ndeal=i=0; i<nplayers; i++) {
          start[i] = ndeal;
          nc = game_params[game].maxhole - nhole[i];
          ndeal += nc;
          end[i] = ndeal;
          for (k=1; k<=nc; k++)
             waste *= k;
       }
       if (waste>1)
          fprintf(stderr, "Due to algorithmic laziness, computation redundancy = %d\n", waste);
       START_NESTED_LOOP_PERM(ndeal,live) {
          INNER_LOOP_HILO8(cards_u hand = uint64_to_cards(hole[i] | (ormask[end[i]] & ~ormask[start[i]])),
                           val[i] = eval(hand),
                           LOval[i] = eval_lowball5(hand));
       } END_NESTED_LOOP_PERM;
#endif
    } break;
    case game_lowball: {
       uint8 start[MAXHANDS], end[MAXHANDS], nc, waste=1;
       for (ndeal=i=0; i<nplayers; i++) {
          start[i] = ndeal;
          nc = game_params[game].maxhole - nhole[i];
          ndeal += nc;
          end[i] = ndeal;
          for (k=1; k<=nc; k++)
             waste *= k;
       }
#if 1
       if (waste>1)
          fprintf(stderr, "Due to algorithmic laziness, computation redundancy >= %d\n", waste);
       START_NESTED_LOOP_PERM(ndeal,live) {
          INNER_LOOP_LO(cards_u hand = uint64_to_cards(hole[i] | (ormask[end[i]] & ~ormask[start[i]])),
                        LOval[i] = eval_lowball5(hand),
                        dum=3);
       } END_NESTED_LOOP_PERM;
#else
#endif
    } break;
    default:
      printf("ERROR: unsupported game\n");
      return 1;
   }

   switch (game) {
    case game_holdem:
    case game_omaha:
      printf("%d board%s containing ", nhands, (nhands==1) ? "" : "s");
      mydump_uint64(NULL,board);
      printf("\n%*s %7s %6s   %7s %6s   %7s %6s     %5s\n",
             game==game_holdem ? -6 : -12,
             "cards", "win", "%win", "lose", "%lose", "tie", "%tie", "EV");
      for (i=0; i<nplayers; i++) {
         mydump_uint64(NULL,hole[i]);
         printf(" %7d %6.2f   %7d %6.2f   %7d %6.2f     %5.3f\n",
                nwin[i], 100.0*nwin[i]/nhands,
                nhands - nwin[i] - ntie[i], 100.0*(nhands - nwin[i] - ntie[i])/nhands,
                ntie[i], 100.0*ntie[i]/nhands,
                ev[i]/nhands);
      }
      break;
    case game_holdem8:
    case game_omaha8:
      printf("%d board%s containing ", nhands, (nhands==1) ? "" : "s");
      mydump_uint64(NULL,board);
      printf("\n%*s%7s   %7s %7s %7s   %7s %7s %7s   %5s\n",
             game==game_holdem8 ? -6 : -12,
             "cards", "scoop",
             "HIwin", "HIlos", "HItie",
             "LOwin", "LOlos", "LOtie",
             "EV");
      for (i=0; i<nplayers; i++) {
         mydump_uint64(NULL,hole[i]);
         printf("%7d   %7d %7d %7d   %7d %7d %7d   %5.3f\n",
                nscoop[i],
                nwin[i], nhands-nwin[i]-ntie[i], ntie[i],
                LOnwin[i], LOnlose[i], LOntie[i],
                ev[i]/nhands);
      }
      break;
    case game_7stud:
      printf("%d possible outcome%s", nhands, (nhands==1) ? "" : "s");
      printf("\n%18s %7s %6s   %7s %6s   %7s %6s     %5s\n",
             "cards", "win", "%win", "lose", "%lose", "tie", "%tie", "EV");
      for (i=0; i<nplayers; i++) {
         mydump_uint64(buf,hole[i]);
         printf("%-18s %7d %6.2f   %7d %6.2f   %7d %6.2f     %5.3f\n",
                buf, nwin[i], 100.0*nwin[i]/nhands,
                nhands - nwin[i] - ntie[i], 100.0*(nhands - nwin[i] - ntie[i])/nhands,
                ntie[i], 100.0*ntie[i]/nhands,
                ev[i]/nhands);
      }
      break;
    case game_7stud8:
      printf("%d possible outcome%s", nhands, (nhands==1) ? "" : "s");
      printf("\n%-18s%6s  %6s %6s %6s  %6s %6s %6s  %5s\n",
             "cards", "scoop",
             "HIwin", "HIlos", "HItie",
             "LOwin", "LOlos", "LOtie",
             "EV");
      for (i=0; i<nplayers; i++) {
         mydump_uint64(buf,hole[i]);
         printf("%-18s%6d  %6d %6d %6d  %6d %6d %6d  %5.3f\n",
                buf, nscoop[i],
                nwin[i], nhands-nwin[i]-ntie[i], ntie[i],
                LOnwin[i], LOnlose[i], LOntie[i],
                ev[i]/nhands);
      }
      break;
    case game_lowball:
      printf("%d possible outcome%s", nhands, (nhands==1) ? "" : "s");
      printf("\n%-17s %7s %6s   %7s %6s   %7s %6s   %5s\n",
             "cards", "win", "%win", "lose", "%lose", "tie", "%tie", "EV");
      for (i=0; i<nplayers; i++) {
         memset(buf,0,sizeof(buf));
         mydump_uint64(buf,hole[i]);
         if (discard[i]) {
            strcat(buf,"/ ");
            mydump_uint64(buf+strlen(buf), discard[i]);
         }
         printf("%-17s %7d %6.2f   %7d %6.2f   %7d %6.2f   %5.3f\n",
                buf, LOnwin[i], 100.0*LOnwin[i]/nhands,
                nhands - LOnwin[i] - LOntie[i], 100.0*(nhands - LOnwin[i] - LOntie[i])/nhands,
                LOntie[i], 100.0*LOntie[i]/nhands,
                ev[i]/nhands);
      }
      break;
    default:
      printf("ERROR: unsupported game\n");
      return 1;
   }
   return 0;
}


PUBLIC int main( int argc, char *argv[] )
{
   if (argc > 1 && strcmp(argv[1],"-f")) {
      return cmpN(argc,argv);
   } else {
      char *fargv[100], buf[1024], *p, *strtok();
      int fargc;

      while (fgets(buf,sizeof(buf),stdin)) {
         fargv[0] = argv[0];
         fargc = 1;
         p = strtok(buf," \t\r\n");
         while (p) {
            fargv[fargc++] = p;
            p = strtok(NULL," \t\r\n");
         }
         cmpN(fargc,fargv);
         fflush(stdout);
      }
   }
   return 0;
}
