#ifndef __ARRAY
#define __ARRAY

extern int max_min_array_size;
extern int intersection_array_size;

int str_length(const char *string);

int *IntersectionArray(int *Arr1, int *Arr2, int lenArr1, int lenArr2);
int countCharOccurences(const char *str, int length, char ch);
char findFirstNonRepeatingChar(const char *str, int length);
char *findLongestCommonPrefix(char **strs, int numStr, int maxLen);
int *MaxMin(int *Arr, int lenArr);

#endif
