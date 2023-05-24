#include "shell.h"
/**
* _strlen - returns the length of a string
* @r: the string whose length to check
*
* Return: integer length of string
*/
int _strl(char *r)
{
	int d = 0;

	if (!r)
		return (0);
	while (*r++)
		d++;
	return (d);
}

/**
* _strcm - performs lexicogarphic comparison of two strangs.
* @str1: the first strang
* @str2: the second strang
*
* Return: negative if str1 < str2, positive if str1 > str2, zero if st* r1 == str2
*/
int _strcm(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
		return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
/**
* starts_hay - checks if needle starts with haystack
* @str: string to search
* @sub: the substring to find
*
* Return: address of next char of haystack or NULL
*/
char *start_hay(const char *str, const char *sub)
{
	while (*sub)
		if (*sub++ != *str++)
			return (NULL);
	return ((char *)str);
}
/**
* _strc - concatenates two strings
* @des: the destination buffer
* @sr: the source buffer
*
* Return: pointer to destination buffer
*/
char *_strc(char *des, char *sr)
{
	char *r = des;

	while (*des != '\0')
		des++;
	while (*sr != '\0')
		*des++ = *sr++;
	*des = *sr;
	return (r);
}
