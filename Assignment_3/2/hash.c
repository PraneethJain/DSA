#include "hash.h"
#include <stdbool.h>
#include <stdio.h>

const int p = 3;
const int size = 1300001;

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

  res[0][0] = str[0] - 'a' + 1;
  res[1][0] = str[length - 1] - 'a' + 1;

  int cur = p;
  for (int i = 1; i < length; ++i)
  {
    res[0][i] = (res[0][i - 1] + ((str[i] - 'a' + 1) * cur) % size) % size;
    res[1][i] = (res[1][i - 1] + ((str[length - 1 - i] - 'a' + 1) * cur) % size) % size;
    cur = (cur * p) % size;
  }

  return res;
}

// Temporary
int raise(int base, int exp)
{
  int res = 1;
  for (int i = 0; i < exp; ++i)
    res = (res * base) % size;

  return res;
}

bool is_palindrome(int *forward_hash, int *reverse_hash, size_t x, size_t y, size_t length)
{
  int t1 = forward_hash[y] - forward_hash[x];
  // printf("%i %i\n", reverse_hash[length - 1 - x], reverse_hash[length - 1 - y]);
  int t2 = reverse_hash[length - 1 - x] - reverse_hash[length - 1 - y];
  int other_t1 = (t1 * raise(p, y - x)) % size;
  int other_t2 = (t2 * raise(p, y - x)) % size;

  // printf("%i %i %i %i\n", t1, t2, other_t1, other_t2);

  return t1 == t2 || t1 == other_t2 || t2 == other_t1;
}
