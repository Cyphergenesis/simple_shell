#include "shell.h"
/**
* **tow - splits a string into words. Repeat delimiters are ignored
* @str: the input string
* @delim: the delimeter string
* Return: a pointer to an array of strings, or NULL on failure
*/
char **tow(char *st, char *delim)
{
	/* j =jed, k = kin, m = mun, numwords = numwo_s, s = p*/
	int i, jed, kin, mun, numwo_s = 0;
	char **p;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; st[i] != '\0'; i++)
	if (!checks_delim(st[i], delim) && (checks_delim(st[i + 1], delim) || !st[i + 1]))
		numwo_s++;
	if (numwo_s == 0)
		return (NULL);
	p = malloc((1 + numwo_s) * sizeof(char *));
	if (!p)
		return (NULL);
	for (i = 0, jed = 0; jed < numwo_s; jed++)
	{
		while (checks_delim(st[i], delim))
			i++;
		kin = 0;
	while (!checks_delim(st[i + kin], delim) && st[i + kin])
		kin++;
	p[jed] = malloc((kin + 1) * sizeof(char));
		if (!p[jed])
		{
			for (kin = 0; kin < jed; kin++)
				free(p[kin]);
			free(p);
			return (NULL);
		}
	mun = 0;
	while (mun < kin)
	{
		p[jed][mun] = st[i++];
		p[jed][mun] = 0;
		mun++;
	}
	}
	p[jed] = NULL;
	return (p);
}

/**
* **tow - splits a string into words
* @str: the input string
* @delim: the delimeter
* Return: a pointer to an array of strings, or NULL on failure
*/
char **tow1(char *str, char delim)
{
	int i, l, d, n, nums = 0;
	char **p;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) || (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
		nums++;
	if (nums == 0)
		return (NULL);
	p = malloc((1 + nums) * sizeof(char *));
	if (!p)
		return (NULL);
	for (i = 0, l = 0; l < nums; l++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		d = 0;
		while (str[i + d] != delim && str[i + d] && str[i + d] != delim)
			d++;
		p[l] = malloc((d + 1) * sizeof(char));
		if (!p[l])
		{
			for (d = 0; d < l; d++)
				free(p[d]);
			free(p);
			return (NULL);
		}
		for (n = 0; n < d; n++)
		{
			p[l][n] = str[i++];
			p[l][n] = 0;
		}
	}
		p[l] = NULL;
	return (p);
}
