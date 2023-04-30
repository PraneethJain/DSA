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