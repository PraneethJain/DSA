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
  h->arr[h->length++] = x;
}

void print(heap *h)
{
  for (int i = 1; i <= h->length; ++i)
    printf("%i ", h->arr[i]);
  printf("\n");
}
