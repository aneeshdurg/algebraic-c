#include <assert.h>
#include "algebraic.h"

newAlgebraic(Tree,
    NewType(Branch);
    NewType(Leaf);

    struct TreeT *l, *r;
    int val;
);

int tree_sum(TreeT root){
  int sum = root.val;
  $(Leaf, root, return sum);
  $(_   , root, { 
      if(root.l)
        sum += tree_sum(*root.l);
      if(root.r)
        sum += tree_sum(*root.r);
      return sum;
  });
}

int main(){
  TreeT a, b, c;
  setType(Branch, a);
  setType(Leaf, b);
  setType(Leaf, c);

  a.val = 1;
  a.l = &b;
  a.r = &c;
  b.val = 2;
  c.val = 3;

  int sum = tree_sum(a);
  assert(sum == 6);
}

