/*
  engraver.hh -- declare Engraver

  source file of the GNU LilyPond music typesetter

  (c) 1996--2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/


#ifndef ENGRAVER_HH
#define ENGRAVER_HH

#include "lily-proto.hh"
#include "array.hh"
#include "request.hh"
#include "score-element-info.hh"
#include "translator.hh"


/**
  a struct which processes requests, and creates the #Score_element#s.
  It may use derived classes. 
  */
class Engraver : public virtual Translator {
    
  friend class Engraver_group_engraver;
protected:
  /// utility
  Paper_def * paper_l() const;
  /**
    Invoke walker method to typeset element. Default: pass on to daddy.
    */
  virtual void typeset_element (Score_element*elem_p);
  /**
    take note of item/spanner
    put item in spanner. Adjust local key; etc.

    Default: ignore the info
    */
  virtual void acknowledge_element (Score_element_info) {}

  /** Do things with stuff found in acknowledge_element. Ugh. Should
     be looped with acknowledge_element.
     
   */
  virtual void process_acknowledged () {}
  /**
    Announce element. Default: pass on to daddy. Utility
    */
  virtual void announce_element (Score_element*, Music*);
  virtual void announce_element (Score_element_info);  
public:
  VIRTUAL_COPY_CONS(Translator);
  Engraver_group_engraver * daddy_grav_l() const;
  /**
    override other ctor
   */
  Engraver () {}
};


#endif // ENGRAVER_HH

