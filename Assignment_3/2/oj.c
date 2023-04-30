#ifndef __HASH_H
#define __HASH_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int *compute_powers(int num, size_t n);
int **hash(char *str, size_t length, int *powers);
bool is_palindrome(int *forward_hash, int *reverse_hash, int x, int y, int length, int *powers);

#endif
#include <stdbool.h>
#include <stdio.h>

const int size = 1572869;

int *compute_powers(int num, size_t n)
{
  int *powers = (int *)malloc(sizeof(int) * n);
  powers[0] = 1;
  for (size_t i = 1; i < n; ++i)
    powers[i] = (powers[i - 1] * num) % size;

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

int main()
{
  size_t length;
  int q;
  scanf("%zu %i", &length, &q);
  char str[length + 1];
  scanf("%s", str);
  int *powers = compute_powers(2, length);
  int **res = hash(str, length, powers);
  int *forward_hash = res[0];
  int *reverse_hash = res[1];

  // for (int i = 0; i < length; ++i)
  //   printf("%i ", forward_hash[i]);
  // printf("\n");
  //
  // for (int i = 0; i < length; ++i)
  //   printf("%i ", reverse_hash[i]);
  // printf("\n");

  size_t l, r;
  for (int i = 0; i < q; ++i)
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
