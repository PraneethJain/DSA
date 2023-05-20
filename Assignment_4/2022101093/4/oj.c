#ifndef __HEAP_H
#define __HEAP_H

#include <stdbool.h>
#include <stdio.h>

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

void swap(int *x, int *y);
int max(int x, int y);

typedef struct heap
{
  size_t capacity;
  int *arr;
  size_t length;
} heap;

heap *init_heap(Arena *a, size_t capacity);
void sift_up(heap *h, size_t idx);
void sift_down(heap *h, size_t idx);
void insert(heap *h, int x);
int top(heap *h);
int pop(heap *h);
void decrement_top(heap *h);
bool is_empty(heap *h);
void print(heap *h);

#endif

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
  int temp = *x;
  *x = *y;
  *y = temp;
}

int max(int x, int y)
{
  return x > y ? x : y;
}

heap *init_heap(Arena *a, size_t capacity)
{
  heap *h = (heap *)a->arena_alloc(a, sizeof(heap));

  h->capacity = capacity;
  h->length = 0;
  h->arr = (int *)a->arena_alloc(a, sizeof(int) * (capacity + 1));

  return h;
}

void sift_up(heap *h, size_t idx)
{
  size_t cur = idx;
  while (cur != 1 && h->arr[cur] < h->arr[cur / 2])
  {
    swap(&h->arr[cur], &h->arr[cur / 2]);
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
      next_idx = h->arr[2 * cur] < h->arr[2 * cur + 1] ? 2 * cur : 2 * cur + 1;
    else
      next_idx = 2 * cur;

    if (h->arr[cur] > h->arr[next_idx])
      swap(&h->arr[cur], &h->arr[next_idx]);
    else
      break;

    cur = next_idx;
  }
}

void insert(heap *h, int x)
{
  h->arr[++h->length] = x;
  sift_up(h, h->length);
}

int top(heap *h)
{
  return h->arr[1];
}

int pop(heap *h)
{
  int to_return = h->arr[1];

  h->arr[1] = h->arr[h->length--];
  sift_down(h, 1);

  return to_return;
}

void decrement_top(heap *h)
{
  --h->arr[1];
  sift_down(h, 1);
}

bool is_empty(heap *h)
{
  return h->length == 0;
}

void print(heap *h)
{
  for (int i = 1; i <= h->length; ++i)
    printf("%i ", h->arr[i]);
  printf("\n");
}

#define ll long long

int main()
{
  const size_t buffer_length = 1024 * 1024 * 16;
  unsigned char buffer[buffer_length];
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
