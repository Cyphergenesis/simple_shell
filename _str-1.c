#include "shell.h"
/**
* _strcpy - copies a string
* @dest: the destination
* @src: the source
*
* Return: pointer to destination
*/
char *strcp(char *des, char *sr)
{
	int i = 0;
	if (des == sr || sr == 0)
		return (des);
	while (sr[i])
	{
		des[i] = sr[i];
		i++;
	}
	des[i] = 0;
	return (des);
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
	char *r;
	
	if (str == NULL)
	return (NULL);
	while (*str++)
	len++;
	r = malloc(sizeof(char) * (len + 1));if (!r)
		return (NULL);
	for (len++; len--;)
		r[len] = *--str;
	return (r);
}
/**
* putst - prints an input string
* @st: the string to be printed
*
* Return: Nothing
*/
void putst(char *st)
{
	int i = 0;
	if (!st)
		return;
	while (st[i] != '\0')
	{
		putch(st[i]);
		i++;
	}
}
/**
* _putchar - writes the character c to stdout
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int putch(char c)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
		if (c != BUF_FLUSH)
		buff[j++] = c;
		
	return (1);
}
