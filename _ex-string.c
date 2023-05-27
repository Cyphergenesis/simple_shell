#include "shell.h"
/**
 **_strncpy - copies a string
 *@des: the destination string to be copied to
 *@src: the source string
 *@num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *str_cp(char *des, char *src, int num)
{
	int i, k;
	char *b = des;

	i = 0;
	while (src[i] != '\0' && i < num - 1)
	{
		des[i] = src[i];
		i++;
	}
	if (i < num)
	{
		k = i;
		while (k < num)
		{
			des[k] = '\0';
			k++;
		}
	}
	return (b);
}
/**
**_str_cat - concatenates two strings
*@des: the first string
*@src: the second string
*@num: the amount of bytes to be maximally used
*Return: the concatenated string
*/
char *_str_cat(char *des, char *src, int num)
{
	int i, k;
	char *b = des;

	i = 0;
	k = 0;
	while (des[i] != '\0')
		i++;
	while (src[k] != '\0' && k < num)
	{
		des[i] = src[k];
		i++;
		k++;
	}
	if (k < num)
		des[i] = '\0';
	return (b);

}
/**
**locate_str - locates a character in a string
*@str: the string to be parsed
*@c: the character to look for
*Return: (s) a pointer to the memory area s
*/
char *locate_str(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);

}
