#include "trie.h"

int main()
{
  trie T = create_trie_node();

  insert(T, "h", 1);
  insert(T, "hh", 2);
  insert(T, "hhh", 3);

  print_trie(T);
  delete(T, "hh", 2);
  print_trie(T);
  delete(T, "hhh", 3);
  print_trie(T);
  delete(T, "h", 1);
  print_trie(T);

  insert(T, "praneeth", 8);
  print_trie(T);

  return 0;
}
