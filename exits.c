#include "shell.h"
/**
**str_cp - copies a string
*@dest: the destination string to be copied to
*@src: the source string
*@n: the amount of characters to be copied
*Return: the concatenated string
*/
char *str_cp(char *dest, char *src, int n)
{
	int i, k;
	char *p = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		k = i;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (p);
}
/**
**_str-cat - concatenates two strings
*@dest: the first string
*@src: the second string
*@n: the amount of bytes to be maximally used
*Return: the concatenated string
*/
char *_str_cat(char *dest, char *src, int n)
{
	int i, k;
	char *p = dest;

	i = 0;
	k = 0;
	while (dest[i] != '\0')
		i++;
	while (src[k] != '\0' && k < n)
	{
		dest[i] = src[k];
		i++;
		k++;
	}
	if (k < n)
		dest[i] = '\0';
	return (p);
}
/**
**locate-str - locates a character in a string
*@s: the string to be parsed
*@c: the character to look for
*Return: (s) a pointer to the memory area s
*/
char *locate_str(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
