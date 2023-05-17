#include "heap.h"

#define ll long long

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  size_t T;
  scanf("%zu", &T);
  for (size_t i = 0; i < T; ++i)
  {
    heap *h = init_heap(&a, 400000);

    size_t N, K;
    scanf("%zu %zu", &N, &K);
    int score;
    for (size_t j = 0; j < N; ++j)
    {
      scanf("%i", &score);
      insert(h, score);
    }

    ll res = 0;
    for (size_t j = 0; j < K; ++j)
    {
      res += top(h);
      decrement_top(h);
    }

    printf("%lli\n", res);

    a.arena_free(&a);
  }

  return 0;
}
