/*
  align-item.hh -- declare Align_elem

  source file of the GNU LilyPond music typesetter

  (c)  1997--2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/


#ifndef VERTICAL_ALIGN_ITEM_HH
#define VERTICAL_ALIGN_ITEM_HH

#include "axis-group-element.hh"
#include "interval.hh"
#include "direction.hh"
#include "axes.hh"
#include "hash-table.hh"

/**
  Order elements top to bottom/left to right/right to left etc..

  TODO: implement padding.

  document usage of this.



  *******
  
  element properties

  stacking-dir
  
  Which side to align?  -1: left side, 0: centered (around
     center_l_ if not nil, or around center of width), 1: right side


*/
class Align_element : public virtual Axis_group_element {
public:
  Axis axis () const;

  void set_axis (Axis);
  int get_count (Score_element*)const;
  void add_element (Score_element *);
  static Real alignment_callback (Dimension_cache const *);
protected:
  virtual void do_side_processing (Axis);
  
};
#endif // VERTICAL_ALIGN_ITEM_HH
