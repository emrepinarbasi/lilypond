/*
  p-score.hh -- declare PScore

  source file of the GNU LilyPond music typesetter

  (c) 1996,1997 Han-Wen Nienhuys <hanwen@stack.nl>
*/


#ifndef P_SCORE_HH
#define P_SCORE_HH

#include "colhpos.hh"
#include "parray.hh"
#include "lily-proto.hh"
#include "plist.hh"

/** all stuff which goes onto paper. notes, signs, symbols in a score
     #PScore# contains the items, the columns.
    
    */

class PScore {
public:
    Paper_def *paper_l_;

    /// the columns, ordered left to right
    Pointer_list<PCol *> cols;

    /// the idealspacings, no particular order
    Pointer_list<Idealspacing*> suz;

    /// crescs etc; no particular order
    Pointer_list<Spanner *> spanners;

    /// other elements
    Pointer_list<Score_elem*> elem_p_list_;
    
    Super_elem *super_elem_l_;

    /* *************** */
    /* CONSTRUCTION */
    
    PScore(Paper_def*);
    /// add a line to the broken stuff. Positions given in #config#
    void set_breaking(Array<Col_hpositions> const &);

    /** add an item.
       add the item in specified containers. If breakstatus is set
       properly, add it to the {pre,post}break of the pcol.
       */
    void typeset_item(Item *item_p,  PCol *pcol_l,int breakstatus=1);

    ///    add to bottom of pcols
    void add(PCol*);

    /**
      @return argument as a cursor of the list
      */
    PCursor<PCol *> find_col(PCol const *)const;

    Link_array<PCol> col_range(PCol *left_l, PCol *right_l) const;
    Link_array<PCol> breakable_col_range(PCol*,PCol*) const;
    Link_array<PCol> broken_col_range(PCol*,PCol*) const;
    
    /* MAIN ROUTINES */
    void process();

    /// last deed of this struct
    void output(Tex_stream &ts);

    /* UTILITY ROUTINES */

    /// get the spacing between c1 and c2, create one if necessary.
    Idealspacing* get_spacing(PCol *c1, PCol *c2);

    /// connect c1 and c2
    void do_connect(PCol *c1, PCol *c2, Real distance_f, Real strength_f);

    /// connect c1 and c2 and any children of c1 and c2
    void connect(PCol* c1, PCol *c2, Real distance_f,Real  strength_f= 1.0);
    
    /* STANDARD ROUTINES */
    void OK()const;
    void print() const;
    ~PScore();
    void typeset_element(Score_elem*);
    void typeset_broken_spanner(Spanner*);
    /// add a Spanner
    void typeset_unbroken_spanner(Spanner*);
 
    
private:
    /// before calc_breaking
    void preprocess();

    /// calculate where the lines are to be broken, and use results
    void calc_breaking();

    /// after calc_breaking
    void postprocess();
    
    /// delete unused columns
    void clean_cols();
};

#endif
