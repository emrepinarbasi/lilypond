/*
  my-lily-parser.cc -- implement My_lily_parser

  source file of the GNU LilyPond music typesetter

  (c)  1997--2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
       Jan Nieuwenhuizen <janneke@gnu.org>
*/

#include "my-lily-parser.hh"
#include "my-lily-lexer.hh"
#include "debug.hh"
#include "main.hh"
#include "parser.hh"
#include "file-results.hh"
#include "scope.hh"

My_lily_parser::My_lily_parser (Sources * source_l)
{
  source_l_ = source_l;
  lexer_p_ = 0;
  default_duration_ = Duration (2,0);
  error_level_i_ = 0;


  default_header_p_ =0;
}

My_lily_parser::~My_lily_parser()
{
  delete lexer_p_;
  delete default_header_p_;
}

void
My_lily_parser::set_version_check (bool )
{
}

void
My_lily_parser::parse_file (String init, String s)
{
  lexer_p_ = new My_lily_lexer;

  lexer_p_->main_input_str_ = s;

  progress_indication (_("Parsing..."));

  set_yydebug (flower_dstream &&!flower_dstream->silent_b ("Parser"));
  lexer_p_->new_input (init, source_l_);
  do_yyparse ();

  if (!define_spot_array_.empty())
    {
      define_spot_array_.top ().warning (_ ("Braces don't match"));
      error_level_i_ = 1;
    }

  inclusion_global_array = lexer_p_->filename_str_arr_;

  error_level_i_ = error_level_i_ | lexer_p_->errorlevel_i_; // ugh naming.
}

void
My_lily_parser::remember_spot()
{
  define_spot_array_.push (here_input());
}

char const *
My_lily_parser::here_ch_C() const
{
  return lexer_p_->here_ch_C();
}

void
My_lily_parser::parser_error (String s)
{
  here_input().error (s);
  error_level_i_ = 1;
  exit_status_i_ = 1;
}

void
My_lily_parser::set_last_duration (Duration const *d)
{
  default_duration_ = *d;
}


Input
My_lily_parser::pop_spot()
{
  return define_spot_array_.pop();
}

Input
My_lily_parser::here_input() const
{
  return  lexer_p_->here_input ();
}

// move me?
#include "paper-def.hh"
#include "identifier.hh"
#include "translator-def.hh"

My_lily_parser * current_parser;

MAKE_SCHEME_CALLBACK(My_lily_parser,paper_description, 0);

SCM
My_lily_parser::paper_description ()
{
  My_lily_parser * me = current_parser;

  Identifier *id = unsmob_identifier (me->lexer_p_->lookup_identifier ("$defaultpaper"));
  Paper_def *p = dynamic_cast<Paper_def*> (id->access_content_Music_output_def (false));

  SCM al = p->translator_p_dict_p_->to_alist ();
  SCM l = SCM_EOL;
  for (SCM s = al ; gh_pair_p (s); s = gh_cdr (s))
    {
      Translator_def * td = unsmob_translator_def (gh_cdar (s));
      l = gh_cons (gh_cons (gh_caar (s), td->to_alist ()),  l);
    }
  return l;  
}
  

