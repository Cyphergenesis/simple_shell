#include "shell.h"
/**
* con_str - converts a string to an integer
* @s: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*
-1 on error
*/
int con_str(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++; /* TODO: why does this make main return 255? */
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
		return (-1);
	}
	return (res);
}
/**
* _error - prints an error message
* @f: the parameter & return info struct
* @estr: string containing specified error type
* Return: 0 if no numbers in string, converted number otherwise
*
-1 on error
*/
void _error(sort *f, char *estr)
{
	_write_str(f->fname);
	_write_str(": ");
	print_func(f->line_count, STDERR_FILENO);
	_write_str(": ");
	_write_str(f->argv[0]);
	_write_str(": ");
	_write_str(estr);
}
/**
* print_func- function prints a decimal (integer) number (base 10)
* @input: the input
* @fd: the filedescriptor to write to
*
* Return: number of characters printed
*/
int print_func(int input, int fd)
{
	int (*putch)(char) = putch;
	int i, cou = 0;
	unsigned int _abs_, curr;
	
	if (fd == STDERR_FILENO)
		putch = _write;
	if (input < 0)
	{
		_abs_ = -input;
		putch('-');
		cou++;
	}
		else
	{
			_abs_ = input;
	}
			curr = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			putch('0' + curr / i);
			cou++;
		}
		curr %= i;
	}
	putch('0' + curr);
	cou++;
	return (cou);
}
/**
* con_num - converter function, a clone of itoa
* @num: number
* @base: base
* @flags: argument flags
*
* Return: string
*/
char *con_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sgn = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sgn = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" :
"0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sgn)
		*--ptr = sgn;
	return (ptr);
}
/**
* rep_lines - function replaces first instance of '#' with '\0'
* @buf: address of the string to modify
*
* Return: Always 0;
*/
void rep_lines(char *buf)
{
	int p;
	
	for (p = 0; buf[p] != '\0'; p++)
		if (buf[p] == '#' && (!p || buf[p - 1] == ' '))
		{
			buf[p] = '\0';
			break;
		}
}
