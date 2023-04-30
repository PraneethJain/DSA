#include "hash.h"
#include <stdbool.h>
#include <stdio.h>

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

int *compute_powers(Arena *a, int num, size_t n)
{
  int *powers = (int *)a->arena_alloc(a, sizeof(int) * n);
  powers[0] = 1;
  for (size_t i = 1; i < n; ++i)
    powers[i] = (powers[i - 1] * num) % size;

  return powers;
}

// Returns the cumulative hashes in both orders
int **hash(Arena *a, char *str, size_t length, int *powers)
{
  int **res = (int **)a->arena_alloc(a, sizeof(int *) * 2);
  res[0] = (int *)a->arena_alloc(a, sizeof(int) * length);
  res[1] = (int *)a->arena_alloc(a, sizeof(int) * length);

  res[0][0] = str[0] - 'a' + 1;
  res[1][0] = str[length - 1] - 'a' + 1;

  for (int i = 1; i < length; ++i)
  {
    res[0][i] = (res[0][i - 1] + ((str[i] - 'a' + 1) * powers[i]) % size) % size;
    res[1][i] = (res[1][i - 1] + ((str[length - 1 - i] - 'a' + 1) * powers[i]) % size) % size;
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

bool is_palindrome(int *forward_hash, int *reverse_hash, int x, int y, int length, int *powers)
{
  int t1 = forward_hash[y] - (x == 0 ? 0 : forward_hash[x - 1]);
  int t2 = reverse_hash[length - 1 - x] - (y == length - 1 ? 0 : reverse_hash[length - 2 - y]);

  // printf("%i %i\n", t1, t2);
  // printf("%i\n", x + y + 1 - length);
  if (x + y + 1 - length > 0)
    t2 = (t2 * powers[x + y + 1 - length]) % size;
  else
    t1 = (t1 * powers[length - x - y - 1]) % size;

  return t1 == t2;
}
