#ifndef __SORT_H
#define __SORT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

typedef struct pair
{
  int first;
  int second;
} pair;

pair *init_pair(Arena *a, int first, int second);
int cmp_pair(pair *p1, pair *p2);

void swap(pair *x, pair *y);
int min(int x, int y);
int max(int x, int y);

typedef struct heap
{
  size_t capacity;
  pair **arr;
  size_t length;
} heap;

heap *init_heap(Arena *a, size_t capacity);
void sift_up(heap *h, size_t idx);
void sift_down(heap *h, size_t idx);
void insert(heap *h, pair *x);
pair *top(heap *h);
pair *pop(heap *h);
bool is_empty(heap *h);
void print(heap *h);

#endif
