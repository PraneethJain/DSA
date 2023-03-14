#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int max_min_array_size = 0;
int intersection_array_size = 0;

int min(int x, int y) { return x > y ? y : x; }
int max(int x, int y) { return x > y ? x : y; }

int *IntersectionArray(int *Arr1, int *Arr2, int lenArr1, int lenArr2)
{
  int size = min(lenArr1, lenArr2);
  int *res = (int *)malloc(sizeof(int) * size);
  for (int i = 0; i < lenArr1; ++i)
  {
    for (int j = 0; j < lenArr2; ++j)
    {
      if (Arr1[i] == Arr2[j])
      {
        res[intersection_array_size++] = Arr1[i];
        Arr2[j] = 0;
        break;
      }
    }
  }

  return res;
}

int countCharOccurences(const char *str, int length, char ch)
{
  int res = 0;
  for (int i = 0; i < length; ++i)
  {
    res += str[i] == ch;
  }

  return res;
}

char findFirstNonRepeatingChar(const char *str, int length)
{
  for (int i = 0; i < length; ++i)
  {
    int flag = 0;
    for (int j = 0; j < length; ++j)
    {
      if (i == j)
        continue;

      if (str[i] == str[j])
      {
        flag = 1;
        break;
      }
    }
    if (flag == 0)
    {
      return str[i];
    }
  }
  return ' ';
}

int length(const char *string)
{
  if (string[0] == '\0')
    return 0;
  else
  {
    int res = 0;
    while (string[++res] != '\0')
      ;
    return res;
  }
}

void concat(char *destination, const char *source)
{
  int len_destination = length(destination);
  int len_source = length(source);

  for (int i = len_destination; i <= len_destination + len_source; ++i)
  {
    destination[i] = source[i - len_destination];
  }
}

char *findLongestCommonPrefix(char **strs, int numStr, int maxLen)
{
  char *res = (char *)malloc(sizeof(char) * maxLen);
  int flag = 0;
  char c = 0;
  char c_string[2] = {c, '\0'};

  int minLen = maxLen;
  for (int i = 0; i < numStr; ++i)
  {
    int l = length(strs[i]);
    if (l < minLen)
    {
      minLen = l;
    }
  }

  for (int i = 0; i < minLen; ++i)
  {
    flag = 0;
    c = strs[0][i];
    for (int j = 0; j < numStr; ++j)
    {
      if (strs[j][i] != c)
      {
        flag = 1;
        break;
      }
    }
    if (flag)
      break;

    c_string[0] = c;
    concat(res, c_string);
  }
  return res;
}

int *MaxMin(int *Arr, int lenArr)
{
  int runningMax[lenArr];
  int runningMinRev[lenArr];

  runningMax[0] = 0;
  for (int i = 1; i < lenArr; ++i)
  {
    runningMax[i] = max(runningMax[i - 1], Arr[i - 1]);
  }

  runningMinRev[lenArr - 1] = 1000001;
  for (int i = lenArr - 2; i >= 0; --i)
  {
    runningMinRev[i] = min(runningMinRev[i + 1], Arr[i + 1]);
  }

  int *res = (int *)malloc(sizeof(int) * lenArr);
  for (int i = 0; i < lenArr; ++i)
  {
    if (Arr[i] > runningMax[i] && Arr[i] < runningMinRev[i])
    {
      res[max_min_array_size++] = i;
    }
  }
  return res;
}

// int main()
// {

//   int n1, n2;
//   scanf("%i %i", &n1, &n2);
//   int arr1[n1];
//   int arr2[n2];
//   for (int i = 0; i < n1; ++i)
//   {
//     scanf("%i", &arr1[i]);
//   }
//   for (int i = 0; i < n2; ++i)
//   {
//     scanf("%i", &arr2[i]);
//   }

//   for (int i = 0; i < n1; ++i)
//   {
//     printf("%i ", arr1[i]);
//   }
//   printf("\n");
//   for (int i = 0; i < n2; ++i)
//   {
//     printf("%i ", arr2[i]);
//   }
//   printf("\n");


//   // int *res = IntersectionArray(arr1, arr2, n1, n2);

//   // for (int i = 0; i < intersection_array_size; ++i)
//   // {
//   //   printf("%i ", res[i]);
//   // }
//   // printf("\n");
// }