#include "shell.h"
/**
* _write_str - prints an input string
* @str: the string to be printed
*
* Return: Nothing
*/
void _write_str(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_write(str[i]);
		i++;
	}
}
/*** _write - writes the character c to stderr
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _write(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}
/**
* write_fd- writes the character c to given fd
* @c: The character to print
* @fd: The filedescriptor to write to
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int write_fd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}
/**
* _print_string - prints an input string
* @str: the string to be printed
* @fd: the filedescriptor to write to*
* Return: the number of chars put
*/
int _print_string(char *str, int fd)
{
	int k = 0;
	
	if (!str)
		return (0);
	while (*str)
	{
		k += write_fd(*str++, fd);
	}
	return (k);
}
