#ifndef __HEAP_H
#define __HEAP_H

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
int top(heap *h);
int pop(heap *h);
bool is_empty(heap *h);
heap *heapify(Arena *a, int *arr, size_t length);
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

void swap(int *x, int *y)
{
  int temp = *x;
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

heap *init_heap(Arena *a, size_t capacity)
{
  heap *h = (heap *)a->arena_alloc(a, sizeof(heap));

  h->capacity = capacity;
  h->length = 0;
  h->arr = (int *)a->arena_alloc(a, sizeof(int) * (capacity + 1));

  return h;
}

void sift_up(heap *h, size_t idx)
{
  size_t cur = idx;
  while (cur != 1 && h->arr[cur] < h->arr[cur / 2])
  {
    swap(&h->arr[cur], &h->arr[cur / 2]);
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
      next_idx = h->arr[2 * cur] < h->arr[2 * cur + 1] ? 2 * cur : 2 * cur + 1;
    else
      next_idx = 2 * cur;

    if (h->arr[cur] > h->arr[next_idx])
      swap(&h->arr[cur], &h->arr[next_idx]);
    else
      break;

    cur = next_idx;
  }
}

void insert(heap *h, int x)
{
  h->arr[++h->length] = x;
  sift_up(h, h->length);
}

int top(heap *h)
{
  return h->arr[1];
}

int pop(heap *h)
{
  int to_return = h->arr[1];

  h->arr[1] = h->arr[h->length--];
  sift_down(h, 1);

  return to_return;
}

bool is_empty(heap *h)
{
  return h->length == 0;
}

heap *heapify(Arena *a, int *arr, size_t length)
{
  heap *h = (heap *)a->arena_alloc(a, sizeof(heap));
  h->capacity = length;
  h->arr = (int *)a->arena_alloc(a, sizeof(int) * length + 1);
  for (size_t i = 1; i <= length; ++i)
    h->arr[i] = arr[i];

  h->length = length;
  h->arr[length + 1] = h->arr[length];

  for (size_t i = length / 2; i > 0; --i)
  {
    int min_val = min(h->arr[i], h->arr[2 * i], h->arr[2 * i + 1]);
    if (min_val == h->arr[2 * i])
      swap(&h->arr[i], &h->arr[2 * i]);
    else if (min_val == h->arr[2 * i + 1])
      swap(&h->arr[i], &h->arr[2 * i + 1]);
  }

  return h;
}

void print(heap *h)
{
  for (int i = 1; i <= h->length; ++i)
    printf("%i ", h->arr[i]);
  printf("\n");
}

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  size_t length;
  scanf("%zu", &length);

  heap *h = init_heap(&a, 100000);
  int arr[length + 1];
  for (size_t i = 1; i <= length; ++i)
  {
    scanf("%i", &arr[i]);
    insert(h, arr[i]);
  }

  int res[length + 1];
  size_t cur_index = 1;
  while (!is_empty(h))
  {
    if (top(h) == arr[cur_index])
    {
      int x = pop(h);
      res[cur_index++] = pop(h);
      insert(h, x);
    }
    else
      res[cur_index++] = pop(h);
  }

  for (size_t i = 1; i <= length; ++i)
    printf("%i ", res[i]);
  printf("\n");

  a.arena_free(&a);

  return 0;
}
