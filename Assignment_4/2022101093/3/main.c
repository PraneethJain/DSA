#include "sort.h"

int main()
{
  const size_t buffer_length = 1024 * 1024 * 16;
  unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char) * buffer_length);
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  size_t T;
  scanf("%zu", &T);

  for (size_t i = 0; i < T; ++i)
  {
    heap *h = init_heap(&a, 400000);
    size_t N;
    scanf("%zu", &N);

    for (size_t j = 0; j < N; ++j)
    {
      size_t length;
      scanf("%zu", &length);
      char *str = (char *)a.arena_alloc(&a, sizeof(char) * (length + 1));
      scanf("%s", str);
      insert(h, str);
    }

    while (!is_empty(h))
    {
      printf("%s\n", pop(h));
    }

    a.arena_free(&a);
  }

  return 0;
}
