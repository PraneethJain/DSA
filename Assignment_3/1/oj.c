#ifndef __HASH_C
#define __HASH_C

#include <stdio.h>
#include <stdlib.h>

size_t string_length(char *str);

typedef struct Node
{
  char str[16];
  struct Node *next;
} Node;

Node *create_node(char *str);
void print_linked_list(Node *head);
void print_linked_list_reverse(Node *head, int *correct, size_t length);

typedef struct HashTable
{
  size_t size;
  Node **arr;
} HashTable;

HashTable *hashtable_init(size_t size);
int hash(HashTable *h, char *str, size_t length);
void insert(HashTable *h, char *str, size_t length);
void print_anagrams(HashTable *h, char *str, size_t length);
void print_hashtable(HashTable *h);

#endif

const int primes[26] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                        43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

size_t string_length(char *str)
{
  size_t length = 0;
  while (str[length] != '\0')
    ++length;

  return length;
}

Node *create_node(char *str)
{
  Node *n = (Node *)malloc(sizeof(Node));
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

int printed = 0;
void print_linked_list_reverse(Node *head, int *correct, size_t length)
{
  if (head == NULL)
    return;
  print_linked_list_reverse(head->next, correct, length);
  int arr[26] = {0};

  for (int i = 0; i < length; ++i)
    arr[head->str[i] - 'a']++;

  int is_equal = 1;
  for (int i = 0; i < 26; ++i)
  {
    if (arr[i] != correct[i])
    {
      is_equal = 0;
      break;
    }
  }
  if (is_equal)
  {
    printf("%s ", head->str);
    printed = 1;
  }
}

HashTable *hashtable_init(size_t size)
{
  HashTable *h = (HashTable *)malloc(sizeof(HashTable));
  h->arr = (Node **)malloc(sizeof(Node *) * size);
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

void insert(HashTable *h, char *str, size_t length)
{
  int key = hash(h, str, length);
  Node *old_first = h->arr[key];
  Node *new_first = create_node(str);
  new_first->next = old_first;
  h->arr[key] = new_first;
}

void print_anagrams(HashTable *h, char *str, size_t length)
{
  int key = hash(h, str, length);
  int arr[26] = {0};
  for (int i = 0; i < length; ++i)
    arr[str[i] - 'a']++;
  printed = 0;
  print_linked_list_reverse(h->arr[key], arr, length);
  if (!printed)
    printf("-1");

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

int main()
{

  HashTable *h = hashtable_init(13001);
  int n, q;
  scanf("%i %i", &n, &q);
  char s[32];
  for (int i = 0; i < n; ++i)
  {
    scanf("%s", s);
    insert(h, s, string_length(s));
  }

  for (int i = 0; i < q; ++i)
  {
    scanf("%s", s);
    print_anagrams(h, s, string_length(s));
  }

  return 0;
}
