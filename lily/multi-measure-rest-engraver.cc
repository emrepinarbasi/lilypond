/*
  multi_measure_rest-engraver.cc -- implement Multi_measure_rest_engraver

  (c) 1998--2000 Jan Nieuwenhuizen <janneke@gnu.org>
       Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/

#include "proto.hh"
#include "musical-request.hh"
#include "multi-measure-rest.hh"
#include "paper-column.hh"
#include "engraver-group-engraver.hh"
#include "timing-translator.hh"
#include "bar.hh"
#include "staff-symbol-referencer.hh"
#include "engraver.hh"
#include "moment.hh"

/**
 */
class Multi_measure_rest_engraver : public Engraver
{
public:
  VIRTUAL_COPY_CONS(Translator);
  Multi_measure_rest_engraver ();

protected:
  virtual void acknowledge_element (Score_element_info i);
  virtual void do_process_requests ();
  virtual bool do_try_music (Music*);
  virtual void do_pre_move_processing ();
  virtual void do_post_move_processing ();
  virtual void do_removal_processing ();
private:
  Span_req * new_req_l_;
  Span_req * busy_span_req_l_;
  Span_req * stop_req_l_;
  int start_measure_i_;
  Moment start_moment_;
  
  Multi_measure_rest *mmrest_p_;
  Multi_measure_rest *lastrest_p_;
};

ADD_THIS_TRANSLATOR (Multi_measure_rest_engraver);

Multi_measure_rest_engraver::Multi_measure_rest_engraver ()
{
  start_measure_i_ = 0;
  mmrest_p_  = lastrest_p_ =0;
  new_req_l_ = busy_span_req_l_ = stop_req_l_ =0;
}

void
Multi_measure_rest_engraver::acknowledge_element (Score_element_info i)
{
  if (Bar *c = dynamic_cast<Bar*> (i.elem_l_))
    {
      if (mmrest_p_)
	mmrest_p_->add_column (c);
      if (lastrest_p_)
	lastrest_p_->add_column (c);
    }
}

bool
Multi_measure_rest_engraver::do_try_music (Music* req_l)
{
  if (Span_req * sp = dynamic_cast<Span_req*> (req_l))
    {
      if (sp->span_type_str_ == "rest")
	{
	  if (sp->span_dir_ == STOP)
	    {
	      stop_req_l_ = sp;
	    }
	  else if (sp->span_dir_ == START && !new_req_l_)
	    {
	      new_req_l_ = sp;
	    }
	  return true;
	}
    }
  return false;
}



void
Multi_measure_rest_engraver::do_process_requests ()
{
  if (new_req_l_ && stop_req_l_)
    stop_req_l_ = 0;

  if (new_req_l_)
    start_moment_ = now_mom ();

  if (stop_req_l_)
    {
      busy_span_req_l_ =0;
      stop_req_l_ = 0;
    }
  
  if (new_req_l_)
    {
      busy_span_req_l_ = new_req_l_;
      new_req_l_ =0;
    }

  if (busy_span_req_l_ && !mmrest_p_)
    {
      Translator * tr = daddy_grav_l()->get_simple_translator ("Timing_engraver");	// ugh
      Timing_translator * time = dynamic_cast<Timing_translator*> (tr);

      mmrest_p_ = new Multi_measure_rest;
      Staff_symbol_referencer_interface si (mmrest_p_);
      si.set_interface ();

      announce_element (Score_element_info (mmrest_p_, busy_span_req_l_));
      start_measure_i_
	= gh_scm2int (time->get_property ("currentBarNumber", 0));
    }
}

void
Multi_measure_rest_engraver::do_pre_move_processing ()
{
  Moment now (now_mom ());
  Translator * tr = daddy_grav_l()->get_simple_translator ("Timing_engraver");	// ugh
  Timing_translator * time  = dynamic_cast<Timing_translator*> (tr);

  if (mmrest_p_ && (now >= start_moment_) 
    && !time->measure_position ()
    && (scm_ilength (mmrest_p_->get_elt_property ("columns")) >= 2))
    {
      typeset_element (mmrest_p_);
      /*
	must keep mmrest_p_ around to set measures_i_
       */
    }
  if (lastrest_p_)
    {
      typeset_element (lastrest_p_);
      lastrest_p_ = 0;
    }

  if (new_req_l_)
    {
      busy_span_req_l_ = new_req_l_;
      new_req_l_ =0;
    }
  
}

void
Multi_measure_rest_engraver::do_post_move_processing ()
{
  Translator * tr = daddy_grav_l()->get_simple_translator ("Timing_engraver");	// ugh
  Timing_translator * time  = dynamic_cast<Timing_translator*> (tr);

  Moment now (now_mom ());

  if (mmrest_p_ && !time->measure_position ())
    {
      lastrest_p_ = mmrest_p_;
      lastrest_p_->measures_i_
	= gh_scm2int (time->get_property ("currentBarNumber", 0)) - start_measure_i_;
      mmrest_p_ = 0;
    }
}


void
Multi_measure_rest_engraver::do_removal_processing ()
{
  if (mmrest_p_)
    typeset_element (mmrest_p_);
  if (lastrest_p_)
    typeset_element (lastrest_p_);
}
