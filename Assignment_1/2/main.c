#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int T;
  scanf("%i", &T);
  char choice[100];
  for (int i = 0; i < T; ++i) {
    scanf("%s", choice);
    if (strcmp(choice, "OPER1") == 0) {

      int n1, n2;
      int arr1[n1];
      int arr2[n2];
      scanf("%i %i", &n1, &n2);
      for (int i = 0; i < n1; ++i) {
        scanf("%i", &arr1[i]);
      }
      for (int i = 0; i < n2; ++i) {
        scanf("%i", &arr2[i]);
      }
      int *res = IntersectionArray(arr1, arr2, n1, n2);

    } else if (strcmp(choice, "OPER2") == 0) {

      char str[10000];
      scanf("%s", str);
      char c;
      scanf("%c", &c);
      scanf("%c", &c);
      printf("%i\n", countCharOccurences(str, strlen(str), c));

    } else if (strcmp(choice, "OPER3") == 0) {

      char str[10000];
      scanf("%s", str);
      printf("%c\n", findFirstNonRepeatingChar(str, strlen(str)));

    } else if (strcmp(choice, "OPER4") == 0) {

      int n;
      scanf("%i", &n);
      char **strings = (char **)malloc(sizeof(char *) * n);
      for (int i = 0; i < n; ++i) {
        *(strings + i) =
            (char *)malloc(sizeof(char) * 100); // Max size of string is 100
      }

      for (int i = 0; i < n; ++i) {
        scanf("%s", strings[i]);
      }

      char *prefix = findLongestCommonPrefix(strings, n, 100);

      printf("%s\n", prefix);

    } else if (strcmp(choice, "OPER5") == 0) {

      int n;
      scanf("%i", &n);
      int arr[n];
      for (int i = 0; i < n; ++i) {
        scanf("%i", &arr[i]);
      }

      int *indices = MaxMin(arr, n);
      for (int i = 0; i < max_min_array_size; ++i) {
        printf("%i ", indices[i]);
      }
      printf("\n");

    } else {
    }
  }

  return 0;
}
