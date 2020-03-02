/*
  This file is part of LilyPond, the GNU music typesetter.

  Copyright (C) 1997--2020 Han-Wen Nienhuys <hanwen@xs4all.nl>

  LilyPond is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  LilyPond is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with LilyPond.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PAPER_COLUMN_HH
#define PAPER_COLUMN_HH

#include "item.hh"
#include "moment.hh"
#include "rod.hh"

class Paper_column : public Item
{
  int rank_;
  /// if lines are broken then this column is in #line#
  System *system_;

public:
  Paper_column (SCM);
  Paper_column (Paper_column const &);

  Paper_column *clone () const override { return new Paper_column (*this); }
  Paper_column *original () const
  {
    // safe: if there is an original, it is because this was cloned from it
    return static_cast<Paper_column *> (Item::original ());
  }

  Paper_column *get_column () const override;
  System *get_system () const override;
  void set_system (System *);
  bool internal_set_as_bound_of_spanner (Spanner *, Direction) override;

  Paper_column *find_prebroken_piece (Direction d) const
  {
    // This is safe because pieces are clones of the original.
    return static_cast<Paper_column *> (Item::find_prebroken_piece (d));
  }

  // n.b. pointers must not be null
  static bool rank_less (Paper_column *const &a, Paper_column *const &b)
  {
    return a->rank_ < b->rank_;
  }

  int get_rank () const { return rank_; }
  void set_rank (int);

  DECLARE_SCHEME_CALLBACK (print, (SCM));
  DECLARE_SCHEME_CALLBACK (before_line_breaking, (SCM));

  static bool is_musical (Grob *);
  static Moment when_mom (Grob *);
  static bool is_used (Grob *);
  static bool is_breakable (Grob *);
  static bool is_extraneous_column_from_ligature (Grob *);
  static Real minimum_distance (Grob *l, Grob *r);
  static Interval break_align_width (Grob *me, SCM align_sym);
  static Interval get_interface_extent (Grob *column, SCM iface, Axis a);
};

#endif // PAPER_COLUMN_HH
