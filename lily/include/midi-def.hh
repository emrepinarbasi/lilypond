/*
  midi-def.hh -- declare Midi_def

  source file of the GNU LilyPond music typesetter

  (c) 1997--2004 Jan Nieuwenhuizen <janneke@gnu.org>
*/


#ifndef MIDI_DEF_HH
#define MIDI_DEF_HH

#include "lily-proto.hh"
#include "real.hh"
#include "string.hh"
#include "moment.hh"
#include "music-output-def.hh"

/** 
  definitions for midi output. Rather empty
 */
class Midi_def : public Music_output_def
{
  static int score_count_;

public:
  Midi_def ();
  VIRTUAL_COPY_CONSTRUCTOR (Music_output_def, Midi_def);

  int get_tempo (Moment moment);
  void set_tempo (Moment moment, int count_per_minute_i);
};

#endif /* MIDI_DEF_HH */
