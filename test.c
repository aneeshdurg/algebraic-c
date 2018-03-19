#include <assert.h>
#include <stdio.h>
#include "algebraic.h"

NewAlgebraic2(
  Meme,
    Text,   char *text;
            int likes,
    Image,  char *name;
            char *url;
            int likes
);

NewAlgebraic2(
  Tree, 
    Branch, struct TreeT *l;
            struct TreeT *r;
            int val,
    Leaf,   int val
);

int tree_sum(TreeT root){
  $(Leaf, root, return getLeaf(root).val);
  $(_   , root, { 
      int sum = getBranch(root).val;
      if(getBranch(root).l)
        sum += tree_sum(*getBranch(root).l);
      if(getBranch(root).r)
        sum += tree_sum(*getBranch(root).r);
      return sum;
  });
}

int main(){
  TreeT a, b, c;
  setType(Branch, a);
  setType(Leaf, b);
  setType(Leaf, c);

  a.Branch.val = 1;
  a.Branch.l = &b;
  a.Branch.r = &c;
  b.Leaf.val = 2;
  c.Leaf.val = 3;

  int sum = tree_sum(a);
  printf("Sum: %d\n", sum);
  assert(sum == 6);
}

