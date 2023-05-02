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
