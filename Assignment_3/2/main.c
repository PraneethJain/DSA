#include "hash.h"
#include <stdbool.h>
#include <stdio.h>

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  size_t length;
  int q;
  scanf("%lu %i", &length, &q);
  char str[length + 1];
  scanf("%s", str);
  int *powers = compute_powers(&a, 3, length);
  int **res = hash(&a, str, length, powers);
  int *forward_hash = res[0];
  int *reverse_hash = res[1];

  for (int i = 0; i < length; ++i)
    printf("%i ", forward_hash[i]);
  printf("\n");

  for (int i = 0; i < length; ++i)
    printf("%i ", reverse_hash[i]);
  printf("\n");

  size_t l, r;
  for (int i = 0; i < q; ++i)
  {
    scanf("%lu %lu", &l, &r);
    if (is_palindrome(forward_hash, reverse_hash, l - 1, r - 1, length, powers))
      printf("YES");
    else
      printf("NO");
    printf("\n");
  }

  a.arena_free(&a);
  return 0;
}
