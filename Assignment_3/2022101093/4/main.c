#include "heap.h"

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  size_t length;
  scanf("%zu", &length);

  heap *h = init_heap(&a, 100000);
  int arr[length + 1];
  for (size_t i = 1; i <= length; ++i)
  {
    scanf("%i", &arr[i]);
    insert(h, arr[i]);
  }

  int res[length + 1];
  size_t cur_index = 1;
  while (!is_empty(h))
  {
    if (top(h) == arr[cur_index])
    {
      int x = pop(h);
      res[cur_index++] = pop(h);
      insert(h, x);
    }
    else
      res[cur_index++] = pop(h);
  }

  for (size_t i = 1; i <= length; ++i)
    printf("%i ", res[i]);
  printf("\n");

  a.arena_free(&a);

  return 0;
}
