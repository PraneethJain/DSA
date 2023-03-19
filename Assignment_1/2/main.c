#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int T;
  scanf("%i", &T);
  char choice[100];
  for (int i = 0; i < T; ++i)
  {
    scanf("%s", choice);
    char x = choice[4];
    if (x == '1')
    {

      int n1, n2;
      scanf("%i %i", &n1, &n2);
      int arr1[n1];
      int arr2[n2];
      for (int i = 0; i < n1; ++i)
      {
        scanf("%i", &arr1[i]);
      }
      for (int i = 0; i < n2; ++i)
      {
        scanf("%i", &arr2[i]);
      }
      int *res = intersectionArray(arr1, arr2, n1, n2);

      for (int i = 0; i < intersection_array_size; ++i)
      {
        printf("%i ", res[i]);
      }
      printf("\n");
    }
    else if (x == '2')
    {

      char str[10000];
      scanf("%s", str);
      char c;
      scanf("%c", &c);
      scanf("%c", &c);
      printf("%i\n", countCharOccurences(str, str_length(str), c));
    }
    else if (x == '3')
    {

      char str[10000];
      scanf("%s", str);
      char res = findFirstNonRepeatingChar(str, str_length(str));
      if (res == -1)
      {
        printf("-1");
      }
      else
      {
        printf("%c", res);
      }
      printf("\n");
    }
    else if (x == '4')
    {

      int n;
      scanf("%i", &n);
      char **strings = (char **)malloc(sizeof(char *) * n);
      for (int i = 0; i < n; ++i)
      {
        *(strings + i) =
            (char *)malloc(sizeof(char) * 100); // Max size of string is 100
      }
      int temp;
      for (int i = 0; i < n; ++i)
      {
        scanf("%i %s", &temp, strings[i]);
      }

      char *prefix = findLongestCommonPrefix(strings, n, 100);
      if (str_length(prefix) == 0)
      {
        printf("-1");
      }
      else
      {
        printf("%s", prefix);
      }
      printf("\n");
    }
    else if (x == '5')
    {

      int n;
      scanf("%i", &n);
      int arr[n];
      for (int i = 0; i < n; ++i)
      {
        scanf("%i", &arr[i]);
      }

      int *indices = maxMin(arr, n);
      if (max_min_array_size == 0)
      {
        printf("-1");
      }
      else
      {
        for (int i = 0; i < max_min_array_size; ++i)
        {
          printf("%i ", indices[i]);
        }
      }
      printf("\n");
    }
    else if (x == '6')
    {
      int n, m;
      scanf("%i %i", &n, &m);
      char string[n];
      scanf("%s", string);
      char substring[m];
      scanf("%s", substring);

      char *res = removeSubstring(string, n, substring, m);
      if (str_length(res) == 0)
      {
        printf("-1");
      }
      else
      {
        printf("%s", res);
      }
      printf("\n");
    }
  }

  return 0;
}
