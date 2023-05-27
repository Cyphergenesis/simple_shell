#include "shell.h"
/**
* _strl - returns the length of a string
* @s: the string whose length to check
*
* Return: integer length of string
*/
int _strl(char *s)
{
	int i = 0;
	if (!s)
		return (0);
	while (*s++)
		i++;
	return (i);
}
/**
* _strcm- performs lexicogarphic comparison of two strangs.
* @s1: the first strang
* @s2: the second strang
*
* Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int _strcm(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
	return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
* start_hay - checks if needle starts with haystack
* @haystack: string to search
* @needle: the substring to find
*
* Return: address of next char of haystack or NULL
*/
char *start_hay(const char *stack, const char *dle)
{
	while (*dle)
	if (*dle++ != *stack++)
		return (NULL);
	return ((char *)stack);
}
/**
* _strc - concatenates two strings
* @dest: the destination buffer
* @src: the source buffer
*
* Return: pointer to destination buffer
*/
char *_strc(char *dest, char *src)
{
	char *set = dest;
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (set);
}
