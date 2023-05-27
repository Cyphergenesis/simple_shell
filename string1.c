#include "shell.h"
/**
* strcp - copies a string
* @dest: the destination
* @src: the source
*
* Return: pointer to destination
*/
char *strcp(char *dest, char *src)
{
	int i = 0;
	if (dest == src || src == 0)
	return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
return (dest);
}
/**
* _dup - duplicates a string
* @str: the string to duplicate
*
* Return: pointer to the duplicated string
*/
char *_dup(const char *str)
{
	int len = 0;
	char *set;
	if (str == NULL)
		return (NULL);
	while (*str++)
	len++;
	set = malloc(sizeof(char) * (len + 1));
	if (!set)
		return (NULL);
	for (len++; len--;)
	set[len] = *--str;
	return (set);
}
/**
* putst - prints an input string
* @str: the string to be printed
*
* Return: Nothing
*/
void putst(char *str)
{
	int i = 0;
	
	if (!str)
		return;
	while (str[i] != '\0')
	{
		putch(str[i]);
		i++;
	}
}
/**
* putch- writes the character c to stdout
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int putch(char c)
{
	static int h;
	static char buf[WRITE_BUF_SIZE];
	if (c == BUF_FLUSH || h >= WRITE_BUF_SIZE)
	{
		write(1, buf, h);
		h = 0;
	}
	if (c != BUF_FLUSH)
		buf[h++] = c;
	return (1);
}
