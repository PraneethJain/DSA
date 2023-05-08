#include "heap.h"

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  int arr[] = {-1111111, 2, 1, 4, 3, 5, 9, 6, 10, 8, 7};
  size_t length = sizeof(arr) / sizeof(arr[0]) - 1;

  heap *h = heapify(&a, arr, length);
  print(h);

  a.arena_free(&a);

  return 0;
}
