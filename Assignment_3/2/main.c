#include "hash.h"
#include <stdio.h>

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  size_t length = 5;
  char *str = "abbab";
  int **res = hash(&a, str, length);
  int *forward_hash = res[0];
  int *reverse_hash = res[1];

  // for (int i = 0; i < length; ++i)
  //   printf("%i ", forward_hash[i]);
  // printf("\n");
  //
  // for (int i = 0; i < length; ++i)
  //   printf("%i ", reverse_hash[i]);
  // printf("\n");

  a.arena_free(&a);
  return 0;
}
