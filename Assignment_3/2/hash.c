#include "hash.h"
#include <stdio.h>

const int p = 31;

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

// Returns the cumulative hashes in both orders
int **hash(Arena *a, char *str, size_t length)
{
  int **res = (int **)a->arena_alloc(a, sizeof(int *) * 2);
  res[0] = (int *)a->arena_alloc(a, sizeof(int) * length);
  res[1] = (int *)a->arena_alloc(a, sizeof(int) * length);

  for (int i = 0; i < length; ++i)
  {
    res[0][i] = i;
    res[1][length - 1 - i] = i;
  }

  return res;
}
