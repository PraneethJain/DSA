#include "heap.h"

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

int min(int x, int y)
{
  return x > y ? y : x;
}

heap *init_heap(Arena *a, size_t capacity)
{
  heap *h = (heap *)a->arena_alloc(a, sizeof(heap));

  h->capacity = capacity;
  h->length = 0;
  h->arr = (int *)a->arena_alloc(a, sizeof(int) * (capacity + 1));

  return h;
}

void insert(heap *h, int x)
{
  h->arr[++h->length] = x;
  size_t cur = h->length;
  while (cur != 1 && h->arr[cur] < h->arr[cur / 2])
  {
    swap(&h->arr[cur], &h->arr[cur / 2]);
    cur /= 2;
  }
}

int pop(heap *h)
{
  int to_return = h->arr[1];

  h->arr[1] = h->arr[h->length--];
  size_t cur = 1;
  size_t next_idx;
  while (2 * cur <= h->length)
  {
    if (2 * cur + 1 <= h->length)
      next_idx = h->arr[2 * cur] > h->arr[2 * cur + 1] ? 2 * cur + 1 : 2 * cur;
    else
      next_idx = 2 * cur;

    if (h->arr[cur] > h->arr[next_idx])
      swap(&h->arr[cur], &h->arr[next_idx]);
    else
      break;
    cur = next_idx;
  }

  return to_return;
}

void print(heap *h)
{
  for (int i = 1; i <= h->length; ++i)
    printf("%i ", h->arr[i]);
  printf("\n");
}
