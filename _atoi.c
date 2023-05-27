#include "shell.h"
/**
* _active - returns true if shell is interactive mode
* @f: struct address
*
* Return: 1 if interactive mode, 0 otherwise
*/
int _active(sort *f)
{
	return (isatty(STDIN_FILENO) && f->readfd <= 2);
}
/**
* checks_delim - checks if character is a delimeter
* @c: the char to check
* @del: the delimeter string
* Return: 1 if true, 0 if false
*/
int checks_delim(char s, char *del)
{
	while (*del)
	if (*del++ == s)
	return (1);
	return (0);
}
/**
* checks_alpha - checks for alphabetic character
* @c: The character to input
* Return: 1 if c is alphabetic, 0 otherwise
*/
int checks_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
* _convert_str - converts a string to an integer
* @m: the string to be converted* Return: 0 if no numbers in string, converted number otherwise
*/
int _convert_str(char *m)
{
	int i, sgn = 1, flag = 0, output;
	unsigned int res = 0;

	for (i = 0; m[i] != '\0' && flag != 2; i++)
	{
		if (m[i] == '-')
			sgn *= -1;
		if (m[i] >= '0' && m[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (m[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sgn == -1)
		output = -res;
	else
		output = res;
	return (output);
}
