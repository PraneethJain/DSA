#ifndef __HASH_C
#define __HASH_C

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

typedef struct Node
{
  char str[32];
  struct Node *next;
} Node;

void print_linked_list(Node *head);

typedef struct HashTable
{
  size_t size;
  Node **arr;
} HashTable;

HashTable *hashtable_init(Arena *a, size_t size);
int hash(char *str, size_t length);
Node *find(char *str, size_t length);
void print_hashtable(HashTable *h);

#endif
