#include "hash.h"
#include <stdio.h>

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

void print_linked_list(Node *head)
{
  Node *cur = head;
  if (cur == NULL)
    printf("-1");
  else
    while (cur != NULL)
    {
      printf("%s ", cur->str);
      cur = cur->next;
    }

  printf("\n");
}

HashTable *hashtable_init(Arena *a, size_t size)
{
  HashTable *h = (HashTable *)a->arena_alloc(a, sizeof(HashTable));
  h->arr = (Node **)a->arena_alloc(a, sizeof(Node *) * size);
  h->size = size;

  for (size_t i = 0; i < size; ++i)
    h->arr[i] = NULL;

  return h;
}

// Only for debugging
void print_hashtable(HashTable *h)
{
  for (size_t i = 0; i < h->size; ++i)
  {
    printf("%lu ", i);
    print_linked_list(h->arr[i]);
  }
  printf("\n");
}
