/*
  paper-score.hh -- declare Paper_score

  source file of the GNU LilyPond music typesetter

  (c) 1996--2005 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/

#ifndef PAPER_SCORE_HH
#define PAPER_SCORE_HH

#include "column-x-positions.hh"
#include "music-output.hh"

/* LAYOUT output */
class Paper_score : public Music_output
{
  Output_def *layout_;
  System *system_;
  SCM systems_;

public:
  Paper_score (Output_def *);

  Output_def *layout () const;
  System *root_system () const;
  
  void typeset_system (System *);
  Array<Column_x_positions> calc_breaking ();

  SCM get_systems () const;
protected:
  virtual void process ();
  virtual void derived_mark () const;

private:
  Paper_score (Paper_score const &);
};

#endif /* PAPER_SCORE_HH */
