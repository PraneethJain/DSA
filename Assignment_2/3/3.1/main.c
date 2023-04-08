#include "bst.h"
#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  // deq head = (deq)malloc(sizeof(deq_node));
  // head->n = NULL;
  // head->next = head;
  // head->prev = head;
  // head->length = 0;
  // push(head, insert(NULL, 3));
  // printf("%i\n", head->length);
  // push(head, insert(NULL, 4));
  // printf("%i\n", head->length);
  // push(head, insert(NULL, 5));
  // printf("%i\n", head->length);
  // printf("%i\n", pop(head)->val);
  // printf("%i\n", head->length);
  // push_start(head, insert(NULL, 10));
  // printf("%i\n", head->length);
  // pop_rear(head);
  // printf("%i\n", head->length);
  // print(head);
  // print_reverse(head);
  tree T = NULL;
  T = insert(T, 20);
  T = insert(T, 10);
  T = insert(T, 25);
  T = insert(T, 5);
  T = insert(T, 15);
  T = insert(T, 23);
  T = insert(T, 30);
  // pre_order(T);
  // printf("\n");
  zig_zag_order(T);
  printf("\n");

  return 0;
}
