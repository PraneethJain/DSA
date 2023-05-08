#include "heap.h"
#include <stdio.h>

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  heap *h = init_heap(&a, 100000);
  insert(h, 5);
  insert(h, 2);
  insert(h, -19);
  print(h);

  a.arena_free(&a);

  return 0;
}
