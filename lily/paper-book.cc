/*
  paper-book.cc -- implement Paper_book

  source file of the GNU LilyPond music typesetter

  (c) 2004 Jan Nieuwenhuizen <janneke@gnu.org>
*/

#include "ly-module.hh"
#include "main.hh"
#include "page.hh"
#include "paper-book.hh"
#include "output-def.hh"
#include "paper-outputter.hh"
#include "paper-line.hh"
#include "paper-score.hh"
#include "stencil.hh"
#include "warn.hh"


/*
  Ugh. the Function of the Paper_book class is unclear. Trim this
  file.
  
 */


Paper_book::Paper_book ()
{
  pages_ = SCM_BOOL_F;
  lines_ = SCM_BOOL_F;
  copyright_ = SCM_EOL;
  tagline_ = SCM_EOL;
  header_ = SCM_EOL;
  
  bookpaper_ = 0;
  smobify_self ();
}

Paper_book::~Paper_book ()
{
}

#include "ly-smobs.icc"

IMPLEMENT_DEFAULT_EQUAL_P (Paper_book);
IMPLEMENT_SMOBS (Paper_book)
IMPLEMENT_TYPE_P (Paper_book, "ly:paper-book?")

SCM
Paper_book::mark_smob (SCM smob)
{
  Paper_book *b = (Paper_book*) SCM_CELL_WORD_1 (smob);
  for (int i = 0; i < b->score_lines_.size (); i++)
    b->score_lines_[i].gc_mark ();

  scm_gc_mark (b->copyright_);
  if (b->bookpaper_)
    scm_gc_mark (b->bookpaper_->self_scm ());
  scm_gc_mark (b->header_);
  scm_gc_mark (b->pages_);
  scm_gc_mark (b->lines_);
  return b->tagline_;
}

int
Paper_book::print_smob (SCM smob, SCM port, scm_print_state*)
{
  Paper_book *b = (Paper_book*) ly_cdr (smob);
     
  scm_puts ("#<", port);
  scm_puts (classname (b), port);
  scm_puts (" ", port);
  //scm_puts (b->, port);
  scm_puts (">", port);
  return 1;
}

Array<String>
split_string (String s, char c)
{
  Array<String> rv; 
  while (s.length ())
    {
      int i = s.index (c);
      
      if (i == 0)
	{
	  s = s.nomid_string (0, 1);
	  continue;
	}
      
      if (i < 0)
	i = s.length () ;

      rv.push (s.cut_string (0, i));
      s = s.nomid_string (0, i);
    }

  return rv;
}

SCM
dump_fields ()
{
  SCM fields = SCM_EOL;
  for (int i = dump_header_fieldnames_global.size (); i--; )
    fields
      = scm_cons (ly_symbol2scm (dump_header_fieldnames_global[i].to_str0 ()),
		  fields);
  return fields;
}

LY_DEFINE (ly_output_formats, "ly:output-formats",
	   0, 0, 0, (),
	   "Formats passed to --format as a list of strings, "
	   "used for the output.")
{
  Array<String> output_formats = split_string (output_format_global, ',');

  SCM lst = SCM_EOL;
  for (int i = 0; i < output_formats.size (); i ++)
    lst = scm_cons (scm_makfrom0str (output_formats[i].to_str0 ()), lst);
  
  return lst; 
}

/*
  TODO: there is too much code dup, and the interface is not
  clear. FIXME.
 */
void
Paper_book::output (String outname)
{
  if (!score_lines_.size ())
    return;

  
  /* Generate all stencils to trigger font loads.  */
  pages ();

  
  SCM formats = ly_output_formats();
  for (SCM s = formats; ly_c_pair_p (s); s = ly_cdr (s)) 
    {
      String format = ly_scm2string (ly_car (s));
      
      Paper_outputter *out = get_paper_outputter (outname + "." + format, format);
  
      SCM scopes = SCM_EOL;
      if (ly_c_module_p (header_))
	scopes = scm_cons (header_, scopes);
  
      String func_nm = format;
      func_nm = "output-framework-" + func_nm;
	
      SCM func = ly_scheme_function (func_nm.to_str0 ());
      scm_apply_0 (func, scm_list_n (out->self_scm (),
				     self_scm (),
				     scopes,
				     dump_fields (),
				     scm_makfrom0str (outname.to_str0 ()),
				     SCM_UNDEFINED
				     )) ;

      scm_gc_unprotect_object (out->self_scm ());
    }
}


void
Paper_book::classic_output (String outname)
{

  /* Generate all stencils to trigger font loads.  */
  lines ();


  // ugh code dup
  SCM scopes = SCM_EOL;
  if (ly_c_module_p (header_))
    scopes = scm_cons (header_, scopes);

  if (ly_c_module_p (score_lines_[0].header_))
    scopes = scm_cons (score_lines_[0].header_, scopes);
  //end ugh


  Array<String> output_formats = split_string (output_format_global, ',');

  for (int i = 0; i < output_formats.size (); i++)
    {
      String format = output_formats[i];
      String func_nm = format;
      func_nm = "output-classic-framework-" + func_nm;
      
      SCM func = ly_scheme_function (func_nm.to_str0 ());

      Paper_outputter *out = get_paper_outputter (outname + "." + format, format);

      scm_apply_0 (func, scm_list_n (out->self_scm (),
				     self_scm (),
				     scopes,
				     dump_fields (),
				     scm_makfrom0str (outname.to_str0 ()),
				     SCM_UNDEFINED
				     )) ;

      scm_gc_unprotect_object (out->self_scm ());
    }
  
  progress_indication ("\n");
}




LY_DEFINE(ly_paper_book_pages, "ly:paper-book-pages",
	  1,0,0,
	  (SCM pb),
	  "Return pages in book PB.")
{
  return unsmob_paper_book(pb)->pages ();
}


LY_DEFINE(ly_paper_book_lines, "ly:paper-book-lines",
	  1,0,0,
	  (SCM pb),
	  "Return lines in book PB.")
{
  return unsmob_paper_book (pb)->lines ();
}


LY_DEFINE(ly_paper_book_book_paper, "ly:paper-book-book-paper",
	  1,0,0,
	  (SCM pb),
	  "Return pages in book PB.")
{
  return unsmob_paper_book(pb)->bookpaper_->self_scm ();
}

/*

TODO: resurrect more complex user-tweaks for titling .

*/
Stencil
Paper_book::book_title ()
{
  SCM title_func = bookpaper_->lookup_variable (ly_symbol2scm ("book-title"));
  Stencil title;

  SCM scopes = SCM_EOL;
  if (ly_c_module_p (header_))
    scopes = scm_cons (header_, scopes);

 
  SCM tit = SCM_EOL;
  if (ly_c_procedure_p (title_func))
    tit = scm_call_2 (title_func,
		     bookpaper_->self_scm (),
		     scopes);

  if (unsmob_stencil (tit))
    title = *unsmob_stencil (tit);

  if (!title.is_empty ())
    title.align_to (Y_AXIS, UP);
  
  return title;
}

  

Stencil
Paper_book::score_title (int i)
{
  SCM title_func = bookpaper_->lookup_variable (ly_symbol2scm ("score-title"));

  Stencil title;

  // ugh code dup
  SCM scopes = SCM_EOL;
  if (ly_c_module_p (header_))
    scopes = scm_cons (header_, scopes);

  if (ly_c_module_p (score_lines_[i].header_))
    scopes = scm_cons (score_lines_[i].header_, scopes);
  //end ugh

  SCM tit = SCM_EOL;
  if (ly_c_procedure_p (title_func))
    tit =scm_call_2 (title_func,
		     bookpaper_->self_scm (),
		     scopes);

  if (unsmob_stencil (tit))
    title = *unsmob_stencil (tit);


  if (!title.is_empty ())
    title.align_to (Y_AXIS, UP);
  
  return title;
}
  

SCM
Paper_book::lines ()
{
  if (SCM_BOOL_F != lines_)
    return lines_;

  lines_ = SCM_EOL;
  Stencil title = book_title ();

  if (!title.is_empty ())
    {
      Paper_line *pl = new Paper_line (title, true);
      
      lines_ = scm_cons (pl->self_scm (), lines_);
      scm_gc_unprotect_object (pl->self_scm ());
    }
  
  int score_count = score_lines_.size ();
  for (int i = 0; i < score_count; i++)
    {
      Stencil title = score_title (i);      
      if (!title.is_empty ())
	{
	  Paper_line *pl = new Paper_line (title, true);
	  lines_ = scm_cons (pl->self_scm (), lines_);
	  scm_gc_unprotect_object (pl->self_scm ());
  	}
      
      if (scm_vector_p (score_lines_[i].lines_) == SCM_BOOL_T)
	{
	  SCM line_list = scm_vector_to_list (score_lines_[i].lines_); // guh.

	  line_list = scm_reverse (line_list);
	  lines_ = scm_append (scm_list_2 (line_list, lines_));
	}
    }
  
  lines_ = scm_reverse (lines_);
  
  int i = 0;
  Paper_line * last = 0;
  for (SCM s = lines_; s != SCM_EOL; s = ly_cdr (s))
    {
      Paper_line * p = unsmob_paper_line (ly_car (s));
      p->number_ = ++i;

      if (last && last->is_title ())
	{
	  p->penalty_ = 10000;	// ugh, hardcoded.
	}
      last = p;
    }

  
  return lines_;
}


SCM
make_tagline (Output_def*paper, SCM scopes)
{
  SCM make_tagline = paper->c_variable ("make-tagline");
  SCM tagline = scm_call_2 (make_tagline, paper->self_scm (), scopes);
  return tagline;
}

SCM
make_copyright (Output_def *paper, SCM scopes)
{
  SCM make_copyright = paper->c_variable ("make-copyright");
  SCM  copyright = scm_call_2 (make_copyright, paper->self_scm (), scopes);
  return copyright;
}

SCM
Paper_book::pages ()
{
  if (SCM_BOOL_F != pages_)
    return pages_;

  pages_ = SCM_EOL;
  
  Output_def *paper = bookpaper_;


  // dummy to extract dims
  Page *page = new Page (SCM_EOL, paper, 1); // ugh
  Real text_height = page->text_height ();

  Real copy_height = 0;
  if (Stencil *s = unsmob_stencil (copyright_))
    copy_height = s->extent (Y_AXIS).length ();

  Real tag_height = 0;
  if (Stencil *s = unsmob_stencil (tagline_))
    tag_height = s->extent (Y_AXIS).length ();

  scm_gc_unprotect_object (page->self_scm ());

  /*
    UGH - move this out of C++.
   */
  SCM scopes = SCM_EOL;
  if (ly_c_module_p (header_))
    scopes = scm_cons (header_, scopes);
  
  tagline_ = make_tagline (bookpaper_, scopes);
  copyright_ = make_tagline (bookpaper_, scopes);


  SCM all = lines ();
  SCM proc = paper->c_variable ("page-breaking");
  SCM pages = scm_apply_0 (proc, scm_list_n (all,
					     self_scm (),
					     scm_make_real (text_height),
					     scm_make_real (-copy_height),
					     scm_make_real (-tag_height),
					     SCM_UNDEFINED));


  SCM *page_tail = &pages_;
  int num = 0;
  for (SCM s = pages; ly_c_pair_p (s); s =  ly_cdr (s))
    {
      Page * page = new Page (ly_car (s), paper, ++num);
      
      *page_tail = scm_cons (page->self_scm () , SCM_EOL);
      page_tail = SCM_CDRLOC(*page_tail);

      scm_gc_unprotect_object (page->self_scm ());

      if (!ly_c_pair_p (ly_cdr (s)))
	page->is_last_ = true;
    }

  return pages_;
}



static SCM
c_ragged_page_breaks (SCM lines,
		      Paper_book *book,
		      Real text_height,
		      Real first, Real last)
{
  int page_number = 0;

  Real book_height =0.;
  for (SCM s = lines ; ly_c_pair_p (s);  s = ly_cdr (s))
    {
      book_height += unsmob_paper_line (ly_car (s))->dim ()[Y_AXIS];
    }

  /*
    UGH. following stuff should go out of C++.
   */
  SCM scopes = SCM_EOL;
  if (ly_c_module_p (book->header_))
    scopes = scm_cons (book->header_, scopes);
  

  SCM tag = make_tagline (book->bookpaper_, scopes);
  if (unsmob_stencil (tag))
    {
      book_height += unsmob_stencil (tag)->extent (Y_AXIS).length ();
    }

  SCM cr = make_copyright (book->bookpaper_, scopes);
  if (unsmob_stencil (cr))
    {
      book_height += unsmob_stencil (cr)->extent (Y_AXIS).length ();
    }

  int page_count = int (book_height / text_height + 0.5); // ceil?
  SCM breaks = SCM_EOL;
  Real page_height = text_height + first;
  Real h = 0;
  int number = 0;
  for (SCM s = lines; ly_c_pair_p (s); s = ly_cdr (s))
    {
      Paper_line *pl = unsmob_paper_line (ly_car (s));
      if (!pl->is_title () && h < page_height)
	number++;
      h += pl->dim ()[Y_AXIS];
      if (!pl->is_title () && h > page_height)
	{
	  breaks = ly_snoc (scm_int2num (number), breaks);
	  page_number++;
	  page_height = text_height + (page_number == page_count) * last;
	  h = 0;
	}
      if (ly_cdr (s) == SCM_EOL)
	breaks = ly_snoc (scm_int2num (pl->number_), breaks);
    }

  return scm_vector (breaks);
}

LY_DEFINE (ly_ragged_page_breaks, "ly:ragged-page-breaks",
	   5, 0, 0, (SCM lines, SCM book, SCM text, SCM first, SCM last),
	   "Return a vector with line numbers of page breaks.")
{
  Paper_book* b = unsmob_paper_book (book);

  SCM_ASSERT_TYPE (scm_pair_p (lines), lines, SCM_ARG1, __FUNCTION__, "list");
  SCM_ASSERT_TYPE (b, book, SCM_ARG2, __FUNCTION__, "Paper_book");
  SCM_ASSERT_TYPE (ly_c_number_p (text), text, SCM_ARG3, __FUNCTION__, "number");
  SCM_ASSERT_TYPE (ly_c_number_p (first), first, SCM_ARG4, __FUNCTION__, "number");
  SCM_ASSERT_TYPE (ly_c_number_p (last), last, SCM_ARG5, __FUNCTION__, "number");

  return c_ragged_page_breaks (lines, b,
			       ly_scm2double (text),
			       ly_scm2double (first), ly_scm2double (last));
}

/****************************************************************/

Score_lines::Score_lines ()
{
  lines_ = SCM_EOL;
  header_ = SCM_EOL;
}

void
Score_lines::gc_mark ()
{
  scm_gc_mark (lines_);
  scm_gc_mark (header_);
}

