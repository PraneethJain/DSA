#include "hash.h"
#include <stdio.h>

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  // int n, q;
  // scanf("%i %i", &n, &q);
  // char s[32];
  // for (int i = 0; i < n; ++i)
  // {
  //   scanf("%s", s);
  //   // Insert string into hashtable
  // }
  //
  // for (int i = 0; i < q; ++i)
  // {
  //   scanf("%s", s);
  //   // Print values of the hashtable
  // }

  HashTable *h = hashtable_init(&a, 31);
  insert(&a, h, "hello", 5);
  insert(&a, h, "elhlo", 5);
  insert(&a, h, "elhl", 4);
  print_hashtable(h);

  a.arena_free(&a);
  return 0;
}
