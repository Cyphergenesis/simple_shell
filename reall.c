#include "shell.h"
/**
* _mem - fills memory with a constant byte
* @p: the pointer to the memory area
* @byte: the byte to fill *s with
* @num: the amount of bytes to be filled
* Return: (s) a pointer to the memory area s
*/
char *_mem(char *p, char byte, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
	p[i] = byte;
	return (p);
}

/**
* _free_str - frees a string of strings
* @qq: string of strings
*/
void _free_str(char **qq)
{
	char **a = qq;

	if (!qq)
		return;
	while (*qq)
		free(*qq++);
	free(a);
}

/**
* _reall - reallocates a block of memory
* @ptr: pointer to previous malloc'ated block
* @old: byte size of previous block
* @new_s: byte size of new block
*
* Return: pointer to da ol'block nameen.
*/
void *_reall(void *ptr, unsigned int old, unsigned int new_s)
{
	char *q;

	if (!ptr)
		return (malloc(new_s));
	if (!new_s)
		return (free(ptr), NULL);
	if (new_s == old)
		return (ptr);
	q = malloc(new_s);
	if (!q)
		return (NULL);

	old = old < new_s ? old : new_s;
	while (old--)
	q[old] = ((char *)ptr)[old];
		free(ptr);
	return (q);
}
