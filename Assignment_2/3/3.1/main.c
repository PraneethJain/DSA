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
    int N;
    scanf("%i", &N);
    int values[N];
    for (int j = 0; j < N; ++j)
      scanf("%i", &values[j]);

    tree t = make_tree(N, values, 0);
    zig_zag_order(t);
    printf("\n");
  }
  return 0;
}
