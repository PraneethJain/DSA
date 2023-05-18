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

int compare(char *str1, char *str2);
void swap(char **x, char **y);

typedef struct heap
{
  size_t capacity;
  char **arr;
  size_t length;
} heap;

heap *init_heap(Arena *a, size_t capacity);
void sift_up(heap *h, size_t idx);
void sift_down(heap *h, size_t idx);
void insert(heap *h, char *x);
char *top(heap *h);
char *pop(heap *h);
void decrement_top(heap *h);
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

int compare(char *str1, char *str2)
{
  size_t idx1 = 0;
  size_t idx2 = 0;
  while (str1[idx1] != '\0' && str2[idx2] != '\0')
  {
    if (str1[idx1] == str2[idx2])
    {
      ++idx1;
      ++idx2;
      continue;
    }

    return str1[idx1] < str2[idx2];
  }

  return str1[idx1] == '\0';
}

void swap(char **x, char **y)
{
  char *temp = *x;
  *x = *y;
  *y = temp;
}

heap *init_heap(Arena *a, size_t capacity)
{
  heap *h = (heap *)a->arena_alloc(a, sizeof(heap));

  h->capacity = capacity;
  h->length = 0;
  h->arr = (char **)a->arena_alloc(a, sizeof(char *) * (capacity + 1));

  return h;
}

void sift_up(heap *h, size_t idx)
{
  size_t cur = idx;
  // while (cur != 1 && h->arr[cur] < h->arr[cur / 2])
  while (cur != 1 && compare(h->arr[cur], h->arr[cur / 2]))
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
      next_idx = compare(h->arr[2 * cur], h->arr[2 * cur + 1]) ? 2 * cur : 2 * cur + 1;
    else
      next_idx = 2 * cur;

    // if (h->arr[cur] > h->arr[next_idx])
    if (compare(h->arr[next_idx], h->arr[cur]))
      swap(&h->arr[cur], &h->arr[next_idx]);
    else
      break;

    cur = next_idx;
  }
}

void insert(heap *h, char *x)
{
  h->arr[++h->length] = x;
  sift_up(h, h->length);
}

char *top(heap *h)
{
  return h->arr[1];
}

char *pop(heap *h)
{
  char *to_return = h->arr[1];

  h->arr[1] = h->arr[h->length--];
  sift_down(h, 1);

  return to_return;
}

void decrement_top(heap *h)
{
  --h->arr[1];
  sift_down(h, 1);
}

bool is_empty(heap *h)
{
  return h->length == 0;
}

void print(heap *h)
{
  for (int i = 1; i <= h->length; ++i)
    printf("%s ", h->arr[i]);
  printf("\n");
}

#define ll long long

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  size_t T;
  scanf("%zu", &T);

  for (size_t i = 0; i < T; ++i)
  {
    heap *h = init_heap(&a, 100000);
    size_t N;
    scanf("%zu", &N);

    for (size_t j = 0; j < N; ++j)
    {
      size_t length;
      scanf("%zu", &length);
      char *str = (char *)a.arena_alloc(&a, sizeof(char) * (length + 1));
      scanf("%s", str);
      insert(h, str);
    }

    while (!is_empty(h))
    {
      printf("%s\n", pop(h));
    }

    a.arena_free(&a);
  }

  return 0;
}
