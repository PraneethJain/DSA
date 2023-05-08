#include "heap.h"
#include <stdio.h>

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  heap *h = init_heap(&a, 100000);

  size_t n;
  scanf("%zu", &n);
  size_t ans = 0;
  int sum = 0;
  for (size_t i = 0; i < n; ++i)
  {
    int cur;
    scanf("%i", &cur);
    ++ans;
    sum += cur;
    insert(h, cur);
    if (sum < 0)
    {
      --ans;
      sum -= pop(h);
    }
  }
  printf("%zu\n", ans);

  a.arena_free(&a);

  return 0;
}
