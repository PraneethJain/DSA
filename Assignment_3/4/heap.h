#ifndef __HEAP_H
#define __HEAP_H

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

void swap(int *x, int *y);
int min(int x, int y, int z);

typedef struct heap
{
  size_t capacity;
  int *arr;
  size_t length;
} heap;

heap *init_heap(Arena *a, size_t capacity);
void insert(heap *h, int x);
int pop(heap *h);
heap *heapify(Arena *a, int *arr, size_t length);
void print(heap *h);

#endif
