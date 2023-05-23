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
    int A[N];
    int B[N];
    for (size_t j = 0; j < N; ++j)
      scanf("%i", &A[j]);
    for (size_t j = 0; j < N; ++j)
      scanf("%i", &B[j]);

    for (size_t j = 0; j < N; ++j)
    {
      pair *p = init_pair(&a, A[j], B[j]);
      insert(h, p);
    }

    pair *p = pop(h);
    int prev_1 = p->first;
    int prev_2 = min(p->first, p->second);
    while (!is_empty(h))
    {
      p = pop(h);
      if (p->second <= p->first && p->second >= prev_2)
        prev_2 = p->second;
      else
        prev_2 = p->first;

      prev_1 = p->first;
    }

    printf("%i %i\n", prev_1, prev_2);
    a.arena_free(&a);
  }

  return 0;
}
