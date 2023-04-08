#include "bst.h"
#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int T;
  scanf("%i", &T);
  for (int i = 0; i < T; ++i)
  {
    tree t = NULL;
    int N;
    scanf("%i", &N);
    int val;
    for (int j = 0; j < N; ++j)
    {
      scanf("%i", &val);
      t = insert(t, val);
    }
    zig_zag_order(t);
  }
  return 0;
}
