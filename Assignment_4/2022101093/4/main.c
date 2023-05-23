#include "sort.h"

int main()
{
  const size_t buffer_length = 1024 * 1024 * 16;
  unsigned char *buffer = (unsigned char *)malloc(sizeof(char) * buffer_length);
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  size_t T;
  scanf("%zu", &T);
  for (size_t t = 0; t < T; ++t)
  {

    size_t K, M;
    scanf("%zu %zu", &K, &M);
    heap *maximums = init_heap(&a, M);
    heap *special = init_heap(&a, M);

    int arr[K][M];
    for (size_t j = 0; j < M; ++j)
      for (size_t i = 0; i < K; ++i)
        scanf("%i", &arr[i][j]);

    size_t J;
    scanf("%zu", &J);

    for (size_t j = 0; j < M; ++j)
    {
      int maxi = -1;
      for (size_t i = 0; i < K; ++i)
      {

        if (i + 1 == J)
          continue;
        maxi = max(maxi, arr[i][j]);
      }

      insert(maximums, maxi);
    }

    for (size_t j = 0; j < M; ++j)
      insert(special, arr[J - 1][j]);

    int ans = 0;
    while (!is_empty(maximums))
    {
      int cur_opponent = pop(maximums);
      while (top(special) < cur_opponent && !is_empty(special))
        pop(special);
      if (is_empty(special))
        break;

      ans++;
      pop(special);
    }

    printf("%i\n", ans);

    a.arena_free(&a);
  }

  return 0;
}
