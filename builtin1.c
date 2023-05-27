#include "shell.h"
/**_display_list - displays the history list, one command by line, preceded
*
with line numbers, starting at 0.
* @f: Structure containing potential arguments. Used to maintain
*
constant function prototype.
* Return: Always 0
*/
int _display_list(sort *f)
{
	list_link(f->history);
	return (0);
}
/**
* unmake_alias - sets alias to string
* @f: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int unmake_alias(sort *f, char *str)
{
	char *q, c;
	int set;
	q = locate_str(str, '=');
	if (!q)
		return (1);
	c = *q;
	*q = 0;
	set = del_node(&(f->alias),
		get_index(f->alias, _node_prefix(f->alias, str, -1)));
	*q = c;
	return (set);
}
/**
* make_alias - sets alias to string
* @info: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int make_alias(sort *f, char *str)
{
	char *q;
	
	q = locate_str(str, '=');
	if (!q)
	return (1);
	if (!*++q)
		return (unmake_alias(f, str));
	unmake_alias(f, str);
	return (_addnode(&(f->alias), str, 0) == NULL);
}
/**
* alias_string - prints an alias string
* @node: the alias node
*
* Return: Always 0 on success, 1 on error
*/
int alias_string(list_t *node)
{
	char *q = NULL, *a = NULL;
	
	if (node)
	{
		q = locate_str(node->str, '=');
		for (a = node->str; a <= q; a++)
			putch(*a);
		putch('\'');
		putst(q + 1);
		putst("'\n");
		return (0);
	}
	return (1);
}
/**
* _alias - mimics the alias builtin (man alias)
* @f: Structure containing potential arguments. Used to maintain
*
constant function prototype.
* Return: Always 0
*/
int _alias(sort *f)
{
	int i = 0;
	char *p = NULL;

	list_t *node = NULL;
	if (f->argc == 1)
	{
		node = f->alias;
		while (node)
		{
			alias_string(node);
			node = node->next;
		}
	return (0);
	}
	for (i = 1; f->argv[i]; i++)
	{
		p = locate_str(f->argv[i], '=');
		if (p)
		make_alias(f, f->argv[i]);
		else
		alias_string(_node_prefix(f->alias, f->argv[i], '='));
	}
	return (0);
}
