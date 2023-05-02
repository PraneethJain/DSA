#include "hash.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define int long long

int32_t main()
{
  size_t length;
  int q;
  scanf("%zu %lli", &length, &q);
  char str[length + 1];
  scanf("%s", str);

  int *powers = compute_powers(37, length);
  int **res = hash(str, length, powers);
  int *forward_hash = res[0];
  int *reverse_hash = res[1];

  size_t l, r;
  for (size_t i = 0; i < q; ++i)
  {
    scanf("%zu %zu", &l, &r);
    if (is_palindrome(forward_hash, reverse_hash, l - 1, r - 1, length, powers))
      printf("YES");
    else
      printf("NO");
    printf("\n");
  }

  return 0;
}
