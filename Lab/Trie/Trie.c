#include "trie.h"

trie create_trie_node()
{
  trie T = (trie)malloc(sizeof(trie_node));
  T->is_word = false;
  for (size_t i = 0; i < 26; ++i)
    T->children[i] = NULL;

  return T;
}

bool exists(trie T, char *str, size_t len)
{
  trie_node *cur = T;
  for (size_t i = 0; i < len; ++i)
  {
    int idx = str[i] - 'a';
    if (cur->children[idx] == NULL)
      return false;
    cur = cur->children[idx];
  }
  return cur->is_word;
}

void insert(trie T, char *str, size_t len)
{
  trie_node *cur = T;
  for (size_t i = 0; i < len; ++i)
  {
    int idx = str[i] - 'a';
    if (cur->children[idx] == NULL)
      cur->children[idx] = create_trie_node();
    cur = cur->children[idx];
  }
  cur->is_word = true;
}

bool has_children(trie T)
{
  for (size_t i = 0; i < 26; ++i)
    if (T->children[i] != NULL)
      return true;
  return false;
}

int count = 0;
void delete(trie T, char *str, size_t len)
{
  if (!exists(T, str, len))
    return;

  trie_node *cur = T;
  trie_node *arr[len];
  for (size_t i = 0; i < len; ++i)
  {
    cur = cur->children[str[i] - 'a'];
    arr[i] = cur;
  }

  if (has_children(cur) || len == 1)
    cur->is_word = false;
  else
    for (size_t i = 0; i < 26; ++i)
      if (arr[len - 2]->children[i] == cur)
        arr[len - 2]->children[i] = NULL;

  for (size_t i = len - 2; i >= 1; --i)
    if (has_children(arr[i]))
      break;
    else
      arr[i] = NULL;
}

void print_string(char *str_arr, size_t length)
{
  for (size_t i = 0; i < length; ++i)
    printf("%c", str_arr[i]);
  printf("\n");
}

size_t length = 0;
char str_arr[512];
void print_trie(trie T)
{
  for (size_t i = 0; i < 26; ++i)
  {
    if (T->children[i] != NULL)
    {
      str_arr[length++] = i + 'a';
      if (T->children[i]->is_word)
        print_string(str_arr, length);
      print_trie(T->children[i]);
      length--;
    }
  }
}
