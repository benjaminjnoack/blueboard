#include "speaker.h"

void init_speaker(void) {

}

void set_speaker_frequency(double hertz) {

}

void play_note(note_t note, octave_t octave) {
  float frequency;

  switch (note) {
    case C:
      frequency = 32.703;
      break;
    case Db:
      frequency = 34.648;
      break;
    case D:
      frequency = 36.708;
      break;
    case Eb:
      frequency = 38.891;
      break;
    case E:
      frequency = 41.203;
      break;
    case F:
      frequency = 43.654;
      break;
    case Gb:
      frequency = 46.246;
      break;
    case G:
      frequency = 48.999;
      break;
    case Ab:
      frequency = 51.913;
      break;
    case A:
      frequency = 55.000;
      break;
    case Bb:
      frequency = 58.270;
      break;
    case B:
      frequency = 61.735;
      break;
  }

  set_speaker_frequency(pow(frequency, (float) octave));
}
