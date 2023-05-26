#include "shell.h"
/**
 *_write_str - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _write_str(char *str)
{
	int i;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_write(str[i]);
		i++;
	}

}

/**
 * _write - writes the character s to stderr
 * @s: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _write(char s)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (s == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (s != BUF_FLUSH)
		buf[j++] = s;
	return (1);
}
/**
* write_fd - writes the character c to given fd
* @k: The character to print
* @fd: The filedescriptor to write to
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int write_fd(char k, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (k == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (k != BUF_FLUSH)
		buf[i++] = k;
	return (1);
}
/**
* _print_string - prints an input string
* @str: the string to be printed
* @fd: the filedescriptor to write to*
* Return: the number of chars put
*/
int _print_string(char *ptr, int fd)
{
	int i = 0;

	if (!ptr)
		return (0);
	while (*ptr)
	{
		i += write_fd(*ptr++, fd);
	}
	return (i);
}
