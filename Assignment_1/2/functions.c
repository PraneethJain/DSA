#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int max_min_array_size = 0;
int intersection_array_size = 0;

int min(int x, int y) { return x > y ? y : x; }
int max(int x, int y) { return x > y ? x : y; }

int *intersectionArray(int *Arr1, int *Arr2, int lenArr1, int lenArr2)
{
  int f1[10001] = {0};
  for (int i = 0; i < lenArr1; ++i)
  {
    ++f1[Arr1[i]];
  }
  int f2[10001] = {0};
  for (int i = 0; i < lenArr2; ++i)
  {
    ++f2[Arr2[i]];
  }

  int res[lenArr1];
  for (int i = 0; i < 10001; ++i)
  {
    if (f1[i] > 0 && f2[i] > 0)
    {
      res[intersection_array_size++] = i;
    }
  }
  int *intersection_array = (int *)malloc(sizeof(int) * intersection_array_size);
  for (int i = 0; i < intersection_array_size; ++i)
  {
    intersection_array[i] = res[i];
  }
  return intersection_array;
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

int str_length(const char *string)
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
  int len_destination = str_length(destination);
  int len_source = str_length(source);

  for (int i = len_destination; i <= len_destination + len_source; ++i)
  {
    destination[i] = source[i - len_destination];
  }
}

char *findLongestCommonPrefix(char **str, int numStr, int maxLen)
{
  char *res = (char *)malloc(sizeof(char) * maxLen);
  int flag = 0;
  char c = 0;
  char c_string[2] = {c, '\0'};

  int minLen = maxLen;
  for (int i = 0; i < numStr; ++i)
  {
    int l = str_length(str[i]);
    if (l < minLen)
    {
      minLen = l;
    }
  }

  for (int i = 0; i < minLen; ++i)
  {
    flag = 0;
    c = str[0][i];
    for (int j = 0; j < numStr; ++j)
    {
      if (str[j][i] != c)
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

int *maxMin(int *Arr, int lenArr)
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

char *removeSubstring(char *str, int strLength, const char *substr, int substrLength)
{
  int is_equal;
  int cur_res_length = 0;
  char *res = (char *)malloc(sizeof(char) * strLength);
  for (int i = 0; i < strLength; ++i)
  {
    is_equal = 1;
    if (i + substrLength > strLength)
    {
      is_equal = 0;
    }
    else
    {
      for (int j = 0; j < substrLength; ++j)
      {
        if (str[i + j] != substr[j])
        {
          is_equal = 0;
          break;
        }
      }
    }
    if (!is_equal)
    {
      res[cur_res_length++] = str[i];
    }
    else
    {
      i += substrLength - 1;
    }
  }
  return res;
}
