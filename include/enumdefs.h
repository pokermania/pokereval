#define ENUM_MAXPLAYERS 12

typedef enum {
  game_holdem,
  game_holdem8,
  game_omaha,
  game_omaha8,
  game_7stud,
  game_7stud8,
  game_7studnsq,
  game_razz,
  game_5draw,
  game_5draw8,
  game_5drawnsq,
  game_lowball,
  game_lowball27,
  game_NUMGAMES
} enum_game_t;

typedef struct {
  enum_game_t	game;
  int           minpocket;
  int           maxpocket;
  int          	maxboard;
  int		haslopot;
  int		hashipot;
  char *	name;
} enum_gameparams_t;

typedef enum { ENUM_EXHAUSTIVE, ENUM_SAMPLE } enum_sample_t;

typedef struct {
  unsigned int nplayers;
  unsigned int nwinhi[ENUM_MAXPLAYERS];	/* qualifies for high and wins (no tie) */
  unsigned int ntiehi[ENUM_MAXPLAYERS];	/* qualifies for high and ties */
  unsigned int nlosehi[ENUM_MAXPLAYERS];/* qualifies for high and loses */
  unsigned int nwinlo[ENUM_MAXPLAYERS];	/* qualifies for low and wins (no tie) */
  unsigned int ntielo[ENUM_MAXPLAYERS];	/* qualifies for low and ties */
  unsigned int nloselo[ENUM_MAXPLAYERS];/* qualifies for low and loses */
  unsigned int nscoop[ENUM_MAXPLAYERS]; /* wins entire pot */

  /* nsharehi[i][H] is the number of times that player i tied for the best
     high hand with H total players (including player i), or received no
     share of the pot if H=0; likewise for nsharelo. */
  unsigned int nsharehi[ENUM_MAXPLAYERS][ENUM_MAXPLAYERS+1];
  unsigned int nsharelo[ENUM_MAXPLAYERS][ENUM_MAXPLAYERS+1];

  /* nshare[i][H][L] is the number of times that player i tied for the best
     high hand with H total players (including player i) and simultaneously
     tied for the best low hand with L total players (including player i),
     where H=0 and L=0 indicate that player i did not win the corresponding
     share of the pot.  For example, nshare[i][1][1] is the number of times
     that player i scooped both high and low; nshare[i][1][2] is the number of
     times that player i won high and split low with one player.  Note that
     the H=0 and L=0 buckets include cases where player i didn't qualify
     (e.g., for an 8-or-better low), which differs from the definition of
     nlosehi[] and nloselo[] above.  So you can't compute ev[] from
     nshare[][][]. */
  unsigned int nshare[ENUM_MAXPLAYERS][ENUM_MAXPLAYERS+1][ENUM_MAXPLAYERS+1];

  /* ev[i] is the pot equity of player i averaged over all outcomes */
  double ev[ENUM_MAXPLAYERS];

  unsigned int nsamples;
  enum_sample_t sampleType;
  enum_game_t game;
} enum_result_t;  

extern void enumResultPrint(enum_result_t *result, StdDeck_CardMask pockets[],
                            StdDeck_CardMask board);
extern void enumResultClear(enum_result_t *result);
extern int enumExhaustive(enum_game_t game, StdDeck_CardMask pockets[],
                          StdDeck_CardMask board, StdDeck_CardMask dead,
                          int npockets, int nboard, enum_result_t *result);
extern int enumSample(enum_game_t game, StdDeck_CardMask pockets[],
                      StdDeck_CardMask board, StdDeck_CardMask dead,
                      int npockets, int nboard, int niter, enum_result_t *result);
extern enum_gameparams_t *enumGameParams(enum_game_t game);
