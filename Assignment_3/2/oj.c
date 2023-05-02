#ifndef __HASH_H
#define __HASH_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define int long long

int *compute_powers(int num, size_t n);
int **hash(char *str, size_t length, int *powers);
bool is_palindrome(int *forward_hash, int *reverse_hash, int x, int y, int length, int *powers);

#endif

const int size = 3145739;

int *compute_powers(int num, size_t n)
{
  int *powers = (int *)malloc(sizeof(int) * n);
  powers[0] = 1;
  for (size_t i = 1; i < n; ++i)
  {
    powers[i] = (powers[i - 1] * num) % size;
    if (powers[i] < 0)
      powers[i] += size;
  }

  return powers;
}

// Returns the cumulative hashes in both orders
int **hash(char *str, size_t length, int *powers)
{
  int **res = (int **)malloc(sizeof(int *) * 2);
  res[0] = (int *)malloc(sizeof(int) * length);
  res[1] = (int *)malloc(sizeof(int) * length);

  res[0][0] = str[0] - 'a' + 1;
  res[1][0] = str[length - 1] - 'a' + 1;

  for (int i = 1; i < length; ++i)
  {
    res[0][i] = (res[0][i - 1] + ((str[i] - 'a' + 1) * powers[i]) % size) % size;
    if (res[0][i] < 0)
      res[0][i] += size;
    res[1][i] = (res[1][i - 1] + ((str[length - 1 - i] - 'a' + 1) * powers[i]) % size) % size;
    if (res[1][i] < 0)
      res[1][i] += size;
  }

  return res;
}

bool is_palindrome(int *forward_hash, int *reverse_hash, int x, int y, int length, int *powers)
{
  int t1 = (forward_hash[y] - ((x == 0) ? (0) : (forward_hash[x - 1]))) % size;
  int t2 = (reverse_hash[length - 1 - x] - ((y == length - 1) ? (0) : (reverse_hash[length - 2 - y]))) % size;

  if (t1 < 0)
    t1 += size;
  if (t2 < 0)
    t2 += size;

  if (x + y + 1 - length > 0)
  {
    t2 = (t2 * powers[x + y + 1 - length]) % size;
    if (t2 < 0)
      t2 += size;
  }
  else
  {
    t1 = (t1 * powers[length - x - y - 1]) % size;
    if (t1 < 0)
      t1 += size;
  }

  return t1 == t2;
}

int32_t main()
{
  size_t length;
  int q;
  scanf("%zu %lli", &length, &q);
  char str[length + 1];
  scanf("%s", str);

  int *powers = compute_powers(37, length);
  int **res = hash(str, length, powers);
  int *forward_hash = res[0];
  int *reverse_hash = res[1];

  size_t l, r;
  for (size_t i = 0; i < q; ++i)
  {
    scanf("%zu %zu", &l, &r);
    if (is_palindrome(forward_hash, reverse_hash, l - 1, r - 1, length, powers))
      printf("YES");
    else
      printf("NO");
    printf("\n");
  }

  return 0;
}
