#include "shell.h"
/**
* con_str - converts a string to an integer
* @str: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*-1 on error
*/
int con_str(char *str)
{
	int i = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res *= 10;
			res += (str[i] - '0');
			if(res > INT_MAX)
				return (-1);
		}
		else
			return(-1);

	}
	return (res);
}

/**
* _error - prints an error message
* @f: the parameter & return info struct
* @str: string containing specified error type
* Return: 0 if no numbers in string, converted number otherwise
*-1 on error
*/
void _error(sort *f, char *str)
{
	_write_str(f->_name);
	_write_str(": ");
	print_func(f->line_count, STDERR_FILENO);
	_write_str(": ");
	_write_str(f->argv[0]);
	_write_str(": ");
	_write_str(str);

}

/**
* print_func - function prints a decimal (integer) number (base 10)
* @inp: the input
* @fd: the filedescriptor to write to
*
* Return: number of characters printed
*/

int print_func(int inp, int fd)
{
	int(*putch)(char) = putch;
	int i, count = 0;

	unsigned int _abs_, curr;

	if(fd == STDERR_FILENO)
		putch = _write;
	if(inp < 0)
	{
		_abs_ = -inp;
		putch('-');
		count++;
	}
	else
	{
		_abs_ = inp;
	}
		curr = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_/i)
		{
			putch('0' + curr / i);
			count++;
		}
		curr %= i;

	}
	putch ('0' + curr);
	count++;
	
	return (count);

}
/**
* con_num - converter function, a clone of itoa
* @num: number
* @b: base
* @flags: argument flags
*
* Return: string
*/
char *con_num(long int num, int b, int flags)
{
	static char *arr;
	static char buff[50];
	char sgn = 0;
	char *ptr;

	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sgn ='-';
	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef":"0123456789ABCDEF";
	
	ptr = &buff[49];
	*ptr = '\0';

	do {
		*--ptr = arr[n % b];
		n /= b;
	}while(n != 0);

	if (sgn)
		*--ptr = sgn;
	return (ptr);
}
/**
* rep_lines - function replaces first instance of '#' with '\0'
* @bf: address of the string to modify
*
* Return: Always 0;
*/
void rep_lines(char *bf)
{
	int j = 0;
	
	for (j = 0; bf[j] != '\0'; j++)
		if (bf[j] == '#' && (!j || bf[j - 1] == ' '))
		{
			bf[j] = '\0';
			break;
		}
}
