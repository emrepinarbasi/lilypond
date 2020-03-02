/*
  This file is part of LilyPond, the GNU music typesetter.

  Copyright (C) 2002--2020 Han-Wen Nienhuys <hanwen@xs4all.nl>

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

#include "music-wrapper-iterator.hh"

#include "context.hh"
#include "input.hh"
#include "international.hh"
#include "music.hh"
#include "warn.hh"

using std::string;

class Context_specced_music_iterator : public Music_wrapper_iterator
{
public:
  DECLARE_SCHEME_CALLBACK (constructor, ());
  void construct_children () override;
};

void
Context_specced_music_iterator::construct_children ()
{
  SCM ct = get_music ()->get_property ("context-type");

  string c_id;
  SCM ci = get_music ()->get_property ("context-id");
  if (scm_is_string (ci))
    c_id = ly_scm2string (ci);
  SCM ops = get_music ()->get_property ("property-operations");
  Direction dir
    = robust_scm2dir (get_music ()->get_property ("search-direction"), CENTER);

  Context *a = 0;

  if (to_boolean (get_music ()->get_property ("create-new")))
    {
      a = get_outlet ()->create_unique_context (dir, ct, c_id, ops);
      if (!a)
        {
          Input *origin = get_music ()->origin ();
          origin->warning (_f ("cannot create context: %s",
                          Context::diagnostic_id (ct, c_id).c_str ()));
        }
    }
  else
    {
      a = get_outlet ()->find_create_context (dir, ct, c_id, ops);
      // Warnings in regression tests would be pretty common if we didn't
      // ignore them for DOWN.
      //
      // TODO: Not warning about a failure in DOWN mode smells funny.  It
      // suggests that the fallback (remaining in the current context) is a
      // fully acceptable alternative (from the perspective of the end user) in
      // all cases; however, that seems unlikely.  But if this is the desired
      // behavior for DOWN mode, should we do it for UP too?
      if (!a && (dir != DOWN))
        {
          Input *origin = get_music ()->origin ();
          origin->warning (_f ("cannot find or create context: %s",
                               Context::diagnostic_id (ct, c_id).c_str ()));
        }
    }

  if (a)
    set_context (a);

  Music_wrapper_iterator::construct_children ();
}

IMPLEMENT_CTOR_CALLBACK (Context_specced_music_iterator);
