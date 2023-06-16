#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Arena
{
  unsigned char *buffer;
  size_t buffer_length;
  size_t offset;
  void *(*arena_alloc)(struct Arena *a, size_t size);
  void (*arena_free)(struct Arena *a);
} Arena;

void arena_init(Arena *a, unsigned char *buffer, size_t buffer_length);
void *arena_alloc(Arena *a, size_t size);
void arena_free(Arena *a);

typedef struct heap
{
  size_t capacity;
  int **arr;
  size_t length;
} heap;

void arena_init(Arena *a, unsigned char *buffer, size_t buffer_length)
{
  a->buffer = buffer;
  a->buffer_length = buffer_length;
  a->offset = 0;
  a->arena_alloc = arena_alloc;
  a->arena_free = arena_free;
}

void *arena_alloc(Arena *a, size_t size)
{
  void *allocated = (void *)(a->buffer + a->offset);
  a->offset += size;
  return allocated;
}

void arena_free(Arena *a)
{
  a->offset = 0;
}

void swap(int *x, int *y)
{
  int a = x[0];
  int b = x[1];
  int c = x[2];
  x[0] = y[0];
  x[1] = y[1];
  x[2] = y[2];
  y[0] = a;
  y[1] = b;
  y[2] = c;
}

heap *init_heap(Arena *a, size_t capacity)
{
  heap *h = (heap *)a->arena_alloc(a, sizeof(heap));

  h->capacity = capacity;
  h->length = 0;
  h->arr = (int **)a->arena_alloc(a, sizeof(int *) * (capacity + 1));
  for (size_t i = 0; i <= capacity; ++i)
    h->arr[i] = (int *)a->arena_alloc(a, sizeof(int) * 3);

  return h;
}

void sift_up(heap *h, size_t idx)
{
  size_t cur = idx;
  while (cur != 1 && h->arr[cur][2] < h->arr[cur / 2][2])
  {
    swap(h->arr[cur], h->arr[cur / 2]);
    cur /= 2;
  }
}

void sift_down(heap *h, size_t idx)
{
  size_t cur = idx;
  size_t next_idx;
  while (2 * cur <= h->length)
  {
    if (2 * cur + 1 <= h->length)
      next_idx = h->arr[2 * cur][2] < h->arr[2 * cur + 1][2] ? 2 * cur : 2 * cur + 1;
    else
      next_idx = 2 * cur;

    if (h->arr[cur][2] > h->arr[next_idx][2])
      swap(h->arr[cur], h->arr[next_idx]);
    else
      break;

    cur = next_idx;
  }
}

void insert(heap *h, int x, int y, int weight)
{
  ++h->length;
  h->arr[h->length][0] = x;
  h->arr[h->length][1] = y;
  h->arr[h->length][2] = weight;
  sift_up(h, h->length);
}

void pop(heap *h, int *x, int *y, int *w)
{
  *x = h->arr[1][0];
  *y = h->arr[1][1];
  *w = h->arr[1][2];

  swap(h->arr[1], h->arr[h->length]);
  --h->length;
  sift_down(h, 1);
}

bool is_empty(heap *h)
{
  return h->length == 0;
}

void print(heap *h)
{
  for (int i = 1; i <= h->length; ++i)
    printf("%i %i %i\n", h->arr[i][0], h->arr[i][1], h->arr[i][2]);
  printf("\n");
}

int main()
{
  const size_t buffer_length = 1024 * 1024 * 16;
  unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char *) * buffer_length);
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  int T;
  scanf("%i", &T);
  for (int t = 0; t < T; ++t)
  {
    int n, m;
    scanf("%i %i", &n, &m);
    int grid[n][m];
    bool known[n][m];
    int costs[n][m];
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < m; ++j)
      {
        scanf("%i", &grid[i][j]);
        known[i][j] = false;
        costs[i][j] = INT_MAX;
      }
    }

    heap *h = init_heap(&a, n * m);
    for (int i = 0; i < n; ++i)
    {
      insert(h, i, 0, grid[i][0]);
      costs[i][0] = grid[i][0];
    }

    for (int j = 1; j < m; ++j)
    {
      insert(h, n - 1, j, grid[n - 1][j]);
      costs[n - 1][j] = grid[n - 1][j];
    }

    int x, y, w;
    while (!is_empty(h))
    {
      pop(h, &x, &y, &w);
      if (known[x][y])
        continue;
      known[x][y] = true;
      int next[8][2] = {{x - 1, y},     {x + 1, y},     {x, y - 1},     {x, y + 1},
                        {x - 1, y - 1}, {x - 1, y + 1}, {x + 1, y - 1}, {x + 1, y + 1}};
      for (int i = 0; i < 8; ++i)
      {
        int nx = next[i][0];
        int ny = next[i][1];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m)
          continue;

        if (w + grid[nx][ny] < costs[nx][ny])
        {
          costs[nx][ny] = w + grid[nx][ny];
          insert(h, nx, ny, costs[nx][ny]);
        }
      }
    }

    int res = INT_MAX;
    for (int i = 0; i < n; ++i)
      if (costs[i][m - 1] < res)
        res = costs[i][m - 1];

    for (int j = 0; j < m; ++j)
      if (costs[0][j] < res)
        res = costs[0][j];

    printf("%i\n", res);
    a.arena_free(&a);
  }

  return 0;
}
