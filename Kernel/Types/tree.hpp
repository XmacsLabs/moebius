/** \file tree.hpp
 *  \copyright GPLv3
 *  \details tree
 *  \author Darcy Shen
 *  \date   2024
 */

#pragma once

#include "observer.hpp"

using lolly::data::A;
using lolly::data::copy;
using lolly::data::is_atomic;
using lolly::data::is_compound;
using lolly::data::is_int;
using lolly::data::lolly_tree_rep;
using lolly::data::operator==;

typedef tree                     scheme_tree;
typedef lolly_tree_rep<observer> tree_rep;

inline int
hash (tree t) {
  if (is_atomic<observer> (t)) return hash (t->label);
  else return t->op ^ hash (A<observer> (t));
}

inline int
hash (array<tree> a) {
  int i, h= 0, n= N (a);
  for (i= 0; i < n; i++) {
    h= (h << 7) + (h >> 25);
    h= h + hash (a[i]);
  }
  return h;
}

inline int
right_index (tree t) {
  return is_atomic (t) ? N (t->label) : 1;
}

inline string
as_string (tree t) {
  return lolly::data::to_string (t);
}

inline tree_rep*
inside (tree t) {
  return t.inside ();
}

inline tree
tree_replace (tree t, tree w, tree b) {
  if (t == w) return b;
  else if (is_atomic (t)) return t;
  else {
    int  i, n= N (t);
    tree r (t, n);
    for (i= 0; i < n; i++)
      r[i]= tree_replace (t[i], w, b);
    return r;
  }
}
