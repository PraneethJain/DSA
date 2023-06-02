#ifndef __TRIE_H
#define __TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct trie_node
{
  struct trie_node *children[26];
  bool is_word;
} trie_node;

typedef trie_node *trie;

trie create_trie_node();
bool exists(trie T, char *str, size_t len);
void insert(trie T, char *str, size_t len);
bool has_children(trie T);
void delete(trie T, char *str, size_t len);
void print_trie(trie T);

#endif
