#ifndef __HASH_H
#define __HASH_H

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

int *compute_powers(Arena *a, int num, size_t n);
int **hash(Arena *a, char *str, size_t length, int *powers);
bool is_palindrome(int *forward_hash, int *reverse_hash, int x, int y, int length, int *powers);

#endif
