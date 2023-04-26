#include "hash.h"
#include <stdio.h>

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);
  int *x = a.arena_alloc(&a, sizeof(int) * 16);
  for (int i = 0; i < 16; ++i)
  {
    x[i] = i;
  }

  for (int i = 0; i < 16; ++i)
  {
    printf("%i ", x[i]);
  }
  printf("\n");

  return 0;
}
