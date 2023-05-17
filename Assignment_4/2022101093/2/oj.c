#ifndef __HEAP_H
#define __HEAP_H

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
int min(int x, int y, int z);

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

void swap(pair *x, pair *y)
{
  pair temp = *x;
  *x = *y;
  *y = temp;
}

int min(int x, int y, int z)
{
  int res = x;
  if (y < res)
    res = y;
  if (z < res)
    res = z;

  return res;
}

pair *init_pair(Arena *a, int first, int second)
{
  pair *p = (pair *)a->arena_alloc(a, sizeof(pair));

  p->first = first;
  p->second = second;

  return p;
}

int cmp_pair(pair *p1, pair *p2)
{
  if (p1->first < p2->first)
    return 1;
  if (p1->first > p2->first)
    return 0;
  if (p1->second < p2->second)
    return 1;

  return 0;
}

heap *init_heap(Arena *a, size_t capacity)
{
  heap *h = (heap *)a->arena_alloc(a, sizeof(heap));

  h->capacity = capacity;
  h->length = 0;
  h->arr = (pair **)a->arena_alloc(a, sizeof(pair *) * (capacity + 1));

  return h;
}

void sift_up(heap *h, size_t idx)
{
  size_t cur = idx;
  while (cur != 1 && cmp_pair(h->arr[cur], h->arr[cur / 2]))
  {
    swap(h->arr[cur], h->arr[cur / 2]);
    cur /= 2;
  }
}

void sift_down(heap *h, size_t idx)
{
  size_t cur = idx;
  size_t next_idx;
  while (2 * cur <= h->length)
  {
    if (2 * cur + 1 <= h->length)
      next_idx = cmp_pair(h->arr[2 * cur], h->arr[2 * cur + 1]) ? 2 * cur : 2 * cur + 1;
    else
      next_idx = 2 * cur;

    if (cmp_pair(h->arr[next_idx], h->arr[cur]))
      swap(h->arr[cur], h->arr[next_idx]);
    else
      break;

    cur = next_idx;
  }
}

void insert(heap *h, pair *x)
{
  h->arr[++h->length] = x;
  sift_up(h, h->length);
}

pair *top(heap *h)
{
  return h->arr[1];
}

pair *pop(heap *h)
{
  pair *to_return = h->arr[1];

  h->arr[1] = h->arr[h->length--];
  sift_down(h, 1);

  return to_return;
}

bool is_empty(heap *h)
{
  return h->length == 0;
}

void print(heap *h)
{
  for (int i = 1; i <= h->length; ++i)
    printf("%i %i\t", h->arr[i]->first, h->arr[i]->second);
  printf("\n");
}

int main()
{
  const size_t buffer_length = 1024 * 1024 * 16;
  unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char) * buffer_length);
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  size_t T;
  scanf("%zu", &T);
  for (size_t i = 0; i < T; ++i)
  {
    heap *h = init_heap(&a, 400000);
    size_t N;
    scanf("%zu", &N);
    int A[N];
    int B[N];
    for (size_t j = 0; j < N; ++j)
      scanf("%i", &A[j]);
    for (size_t j = 0; j < N; ++j)
      scanf("%i", &B[j]);

    for (size_t j = 0; j < N; ++j)
    {
      pair *p = init_pair(&a, A[j], B[j]);
      insert(h, p);
    }
    // print(h);

    pair *p = pop(h);
    int prev_1 = p->first;
    int prev_2 = p->first < p->second ? p->first : p->second;
    // printf("%i %i\n", prev_1, prev_2);
    while (!is_empty(h))
    {
      // print(h);
      p = pop(h);
      if (p->second <= p->first)
      {
        if (p->second >= prev_2)
          prev_2 = p->second;
        else
          prev_2 = p->first;
      }
      else
      {
        prev_2 = p->first;
      }

      prev_1 = p->first;

      // printf("%i %i\n", prev_1, prev_2);
    }

    printf("%i %i\n", prev_1, prev_2);

    a.arena_free(&a);
  }

  return 0;
}
