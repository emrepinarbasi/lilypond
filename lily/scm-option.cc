/*   
  scm-option.cc --  implement option setting from Scheme
  
  source file of the GNU LilyPond music typesetter
  
  (c) 2001--2002  Han-Wen Nienhuys <hanwen@cs.uu.nl>
  
 */

#include <iostream.h>
#include "string.hh"
#include "lily-guile.hh"
#include "scm-option.hh"


/*
  This interface to option setting is meant for setting options are
  useful to a limited audience. The reason for this interface is that
  making command line options clutters up the command-line option name
  space.


  preferably, also dont use TESTING_LEVEL_GLOBAL, since it defeats
  another purpose of this very versatile interface, which is to
  support multiple debug/testing options concurrently.
  
 */


/* Write midi as formatted ascii stream? */
bool midi_debug_global_b;

/* General purpose testing flag */
int testing_level_global;

/*
  crash if internally the wrong type is used for a grob property.
 */
bool internal_type_checking_global_b;

/*

  TODO: verzin iets tegen optie code bloot


  other interesting stuff to add:

@item -T,--no-timestamps
don't timestamp the output

@item -t,--test
Switch on any experimental features.  Not for general public use.

 */

SCM
set_lily_option (SCM var, SCM val)
{
  /*
    Scheme option usage:
    lilypond -e "(set-lily-option 'help 0)"
   */
  if (var == ly_symbol2scm ("help"))
    {
      cout << _("lilypond -e EXPR means

evalute EXPR as Scheme after init.scm has been read.  In particular,
the function set-lily-option allows for access to some internal
variables. Usage:

  (set-lily-option SYMBOL VAL)

possible options for SYMBOL are :
")<<endl;
      
      cout << "  help (any-symbol)"<<endl; 
      cout << "  internal-type-checks #t"<<endl; 
      cout << "  midi-debug (boolean)"<<endl; 
      cout << "  testing-level (int)"<<endl; 

      exit (0);
    }
  else if (var == ly_symbol2scm ("midi-debug"))
    {
      midi_debug_global_b = to_boolean (val);
    }
  else if (var == ly_symbol2scm ("testing-level"))
    {
     testing_level_global = gh_scm2int (val); 
    }
  else if (var == ly_symbol2scm ("internal-type-checks"))
    {
     internal_type_checking_global_b = to_boolean (val); 
    }
  else if (var == ly_symbol2scm ("find-old-relative"))
    {
      /*
	Seems to have been broken for some time!
	
	@item  -Q,--find-old-relative
	show all changes needed to convert a file to  relative octave syntax.


	
      */

      ;
      
    }

  return SCM_UNSPECIFIED;
}


static void
init_functions ()
{
  scm_c_define_gsubr ("set-lily-option", 2, 0, 0, (Scheme_function_unknown)set_lily_option);
}


ADD_SCM_INIT_FUNC (init_functions_sopt, init_functions);


