#ifndef __HASH_C
#define __HASH_C

#include <stdio.h>

size_t string_length(char *str);

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

typedef struct Node
{
  char str[16];
  struct Node *next;
} Node;

Node *create_node(Arena *a, char *str);
void print_linked_list(Node *head);
void print_linked_list_reverse(Node *head);

typedef struct HashTable
{
  size_t size;
  Node **arr;
} HashTable;

HashTable *hashtable_init(Arena *a, size_t size);
int hash(HashTable *h, char *str, size_t length);
void insert(Arena *a, HashTable *h, char *str, size_t length);
void print_anagrams(HashTable *h, char *str, size_t length);
void print_hashtable(HashTable *h);

#endif
#include "hash.h"
#include <stdio.h>

const int primes[26] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                        43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

size_t string_length(char *str)
{
  size_t length = 0;
  while (str[length] != '\0')
    ++length;

  return length;
}

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

Node *create_node(Arena *a, char *str)
{
  Node *n = (Node *)a->arena_alloc(a, sizeof(Node));
  for (size_t i = 0; i < 16; ++i)
    n->str[i] = str[i];
  n->next = NULL;
  return n;
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

void print_linked_list_reverse(Node *head)
{
  if (head == NULL)
    return;
  print_linked_list_reverse(head->next);
  printf("%s ", head->str);
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

int hash(HashTable *h, char *str, size_t length)
{
  int res = 1;
  for (size_t i = 0; i < length; ++i)
  {
    res = (res * primes[str[i] - 'a']) % h->size;
  }
  return res;
}

void insert(Arena *a, HashTable *h, char *str, size_t length)
{
  int key = hash(h, str, length);
  Node *old_first = h->arr[key];
  Node *new_first = create_node(a, str);
  new_first->next = old_first;
  h->arr[key] = new_first;
}

void print_anagrams(HashTable *h, char *str, size_t length)
{
  int key = hash(h, str, length);
  if (h->arr[key] == NULL)
    printf("-1");
  else
    print_linked_list_reverse(h->arr[key]);
  printf("\n");
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

#include "hash.h"
#include <stdio.h>

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  HashTable *h = hashtable_init(&a, 13001);
  int n, q;
  scanf("%i %i", &n, &q);
  char s[32];
  for (int i = 0; i < n; ++i)
  {
    scanf("%s", s);
    insert(&a, h, s, string_length(s));
  }

  for (int i = 0; i < q; ++i)
  {
    scanf("%s", s);
    print_anagrams(h, s, string_length(s));
  }

  a.arena_free(&a);
  return 0;
}

