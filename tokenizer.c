#include "shell.h"
/**
* **tow - splits a string into words. Repeat delimiters are ignored
* @str: the input string
* @d: the delimeter string
* Return: a pointer to an array of strings, or NULL on failure
*/
char **tow(char *str, char *d)
{
	int i, j, kin, m, num_s = 0;
	char **s;
	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
	if (!checks_delim(str[i], d) && (checks_delim(str[i + 1], d) || !str[i + 1]))
	num_s++;
	if (num_s == 0)
		return (NULL);
	s = malloc((1 + num_s) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_s; j++)
	{
			while (checks_delim(str[i], d))
				i++;
		kin = 0;
		while (!checks_delim(str[i + kin], d) && str[i + kin])
			kin++;
		s[j] = malloc((kin + 1) * sizeof(char));
		if (!s[j])
		{
			for (kin = 0; kin < j; kin++)
			free(s[kin]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < kin; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
/**
* **tow - splits a string into words
* @str: the input string
* @d: the delimeter
* Return: a pointer to an array of strings, or NULL on failure
*/
char **tow1(char *str, char d)
{
	int i, j;
	int k, m, num_s = 0;
	char **q;
	if (str == NULL || str[0] == 0)
	return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		(str[i] != d && !str[i + 1]) || str[i + 1] == d)
	num_s++;
		if (num_s == 0)
	return (NULL);
	q = malloc((1 + num_s) * sizeof(char *));
	if (!q)
	return (NULL);
	for (i = 0, j = 0; j < num_s; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		q[j] = malloc((k + 1) * sizeof(char));
		if (!q[j])
		{
			for (k = 0; k < j; k++)
				free(q[k]);
			free(q);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			q[j][m] = str[i++];
		q[j][m] = 0;
	}
	q[j] = NULL;
	return (q);
}
