/*   
'  separating-line-group-engraver.cc --  implement Separating_line_group_engraver
  
  source file of the GNU LilyPond music typesetter
  
  (c) 1998--2003 Han-Wen Nienhuys <hanwen@cs.uu.nl>
  
 */

#include "separating-group-spanner.hh"
#include "separation-item.hh"
#include "paper-column.hh"
#include "paper-def.hh"
#include "engraver.hh"
#include "axis-group-interface.hh"
#include "note-spacing.hh"
#include "group-interface.hh"
#include "accidental-placement.hh"

struct Spacings
{
  Item * staff_spacing_;
  Link_array<Item> note_spacings_;

  Spacings ()
  {
    staff_spacing_ = 0;
  }

  bool empty( )const
  {
    return !staff_spacing_ && !note_spacings_.size (); 
  }
  void clear () {
    staff_spacing_ = 0;
    note_spacings_.clear();
  }
};

class Separating_line_group_engraver : public Engraver
{
protected:
  Item * break_malt_;
  Item * musical_malt_;
  Item * last_musical_malt_;

  Spacings current_spacings_;
  Spacings last_spacings_;
  
  Spanner * sep_span_;
  
  virtual void acknowledge_grob (Grob_info);
  virtual void initialize ();
  virtual void finalize ();
  virtual void stop_translation_timestep ();
  virtual void start_translation_timestep ();  
public:
  TRANSLATOR_DECLARATIONS(Separating_line_group_engraver);
};

Separating_line_group_engraver::Separating_line_group_engraver ()
{
  sep_span_ = 0;
  break_malt_ = 0;
  musical_malt_ =0;
}

void
Separating_line_group_engraver::initialize ()
{
  sep_span_ = new Spanner (get_property ("SeparatingGroupSpanner"));

  announce_grob(sep_span_, SCM_EOL);
  sep_span_->set_bound (LEFT, unsmob_grob (get_property ("currentCommandColumn")));
}

void
Separating_line_group_engraver::finalize ()
{
  SCM ccol = get_property ("currentCommandColumn");
  Grob *column = unsmob_grob (ccol);
  
  sep_span_->set_bound (RIGHT, unsmob_grob (ccol));
  typeset_grob (sep_span_);
  sep_span_ =0;

  for  (int i= 0 ; i < last_spacings_.note_spacings_.size(); i++)
    {
      Pointer_group_interface::add_grob (last_spacings_.note_spacings_[i],
					 ly_symbol2scm ("right-items" ),
					 column);
    }
   
  if(last_spacings_.staff_spacing_
     && last_spacings_.staff_spacing_->get_column () == column)
    {
      last_spacings_.staff_spacing_->suicide ();
    }
}

void
Separating_line_group_engraver::acknowledge_grob (Grob_info i)
{
  Item * it = dynamic_cast <Item *> (i.grob_);
  if (!it)
    return;
  if (it->get_parent (X_AXIS)
      && it->get_parent (X_AXIS)
      ->has_extent_callback_b(Axis_group_interface::group_extent_callback_proc, X_AXIS))
    return;

  
  if (to_boolean (it->get_grob_property ("no-spacing-rods")))
    return ;

  if (Note_spacing::has_interface (it)) 
    {
      current_spacings_.note_spacings_.push (it);
      return ;
    }
  
  bool ib =Item::breakable_b (it);
  Item *&p_ref_ (ib ? break_malt_
		 : musical_malt_);

  if (!p_ref_)
    {
      p_ref_ = new Item (get_property ("SeparationItem"));

      if (ib)
	p_ref_->set_grob_property ("breakable", SCM_BOOL_T);
      announce_grob(p_ref_, SCM_EOL);

      if (p_ref_ == break_malt_)
	{
	  Item *it  = new Item (get_property ("StaffSpacing"));
	  current_spacings_.staff_spacing_ = it;
	  it->set_grob_property ("left-items", gh_cons (break_malt_->self_scm (), SCM_EOL));
	  
	  announce_grob(it, SCM_EOL);

	  if (int i = last_spacings_.note_spacings_.size ())
	    {
	      for (; i--;)
		Pointer_group_interface::add_grob (last_spacings_.note_spacings_[i],
						   ly_symbol2scm ("right-items"),
						   break_malt_);
				     
	    }
	  else if (last_spacings_.staff_spacing_)
	    {
	      
	      last_spacings_.staff_spacing_->set_grob_property ("right-items",
								gh_cons (break_malt_->self_scm(), SCM_EOL));
	    }
	}
    }

  if (Accidental_placement::has_interface (it))
    Separation_item::add_conditional_item (p_ref_, it);
  else
    Separation_item::add_item (p_ref_,it);
}

void
Separating_line_group_engraver::start_translation_timestep ()
{

}

void
Separating_line_group_engraver::stop_translation_timestep ()
{
  if (break_malt_)
    {
      Separating_group_spanner::add_spacing_unit (sep_span_, break_malt_);
      typeset_grob (break_malt_);

      break_malt_ =0;
    }
  
  if (Item * sp = current_spacings_.staff_spacing_)
    {
      /*
	TODO: should really look at the left-items of following
	note-spacing grobs.
       */
      if (musical_malt_)
	Pointer_group_interface::add_grob (sp, ly_symbol2scm ("right-items"),
					   musical_malt_);

      typeset_grob (sp);
    }

  
  if (!current_spacings_.empty ())
    {
      last_spacings_ = current_spacings_;
    }

  current_spacings_.clear ();
  
  if (musical_malt_)
    {
      Separating_group_spanner::add_spacing_unit (sep_span_, musical_malt_);
      typeset_grob (musical_malt_);
    }
  
  musical_malt_ =0;
}


ENTER_DESCRIPTION(Separating_line_group_engraver,
/* descr */       "Generates objects for computing spacing parameters.",
/* creats*/       "SeparationItem SeparatingGroupSpanner",
/* accepts */     "",
/* acks  */      "item-interface",
/* reads */       "",
/* write */       "");
