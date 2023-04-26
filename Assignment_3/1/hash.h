#ifndef __HASH_C
#define __HASH_C

#include <stdio.h>

typedef struct Arena Arena;
struct Arena
{
  unsigned char *buffer;
  size_t buffer_length;
  size_t offset;
  void *(*arena_alloc)(Arena *a, size_t size);
  void (*arena_free)(Arena *a);
};

void arena_init(Arena *a, unsigned char *buffer, size_t buffer_length);
void *arena_alloc(Arena *a, size_t size);
void arena_free(Arena *a);

#endif
