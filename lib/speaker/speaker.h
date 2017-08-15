#include "LPC17xx.h"
#include <math.h>

typedef enum {
  C,
  Db,
  D,
  Eb,
  E,
  F,
  Gb,
  G,
  Ab,
  A,
  Bb,
  B
} note_t;

typedef enum {
  FIRST = 1,
  SECOND,
  THIRD,
  FOURTH,
  FIFTH
} octave_t;

void init_speaker(void);
void set_speaker_frequency(int hertz);
void play_note(note_t note, octave_t octave);
