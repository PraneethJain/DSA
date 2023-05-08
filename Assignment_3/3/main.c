#include "heap.h"
#include <stdio.h>

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  heap *h = init_heap(&a, 100000);
  int x;
  while (1)
  {
    printf("1 to insert\n2 to pop\n");
    scanf("%i", &x);
    if (x == 1)
    {
      scanf("%i", &x);
      insert(h, x);
    }
    else if (x == 2)
    {
      printf("Popped: %i\n", pop(h));
    }
    else
    {
      break;
    }
    printf("\n");
    printf("Heap: ");
    print(h);
  }

  a.arena_free(&a);

  return 0;
}
