#include "heap.h"

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  size_t length;
  scanf("%zu", &length);

  int arr[length + 1];
  for (size_t i = 1; i <= length; ++i)
    scanf("%i", &arr[i]);

  heap *h = heapify(&a, arr, length);
  print(h);

  a.arena_free(&a);

  return 0;
}
