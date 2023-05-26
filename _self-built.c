#include "shell.h"
/** 
 * _display_list - displays the history list, one command by line, 
 * preced with line numbers, starting at 0.
 * @f: Structure containing potential arguments. Used to maintain
 * constant function prototype.
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
	char *b, n;
	int net;

	b = locate_str(str, '=');
	if(!b)
		return (1);
	n = *b;
	*b = 0;
	net  = del_node(&(f->alias), get_index(f->alias, _node_prefix(f->alias, str, -1)));
	*b = n;
	return (net);

}

/**
* make_alias - sets alias to string
* @f: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int make_alias(sort *f, char *str)
{
	char *m;
	m = locate_str(str, '=');
	if(!m)
		return (1);
	
	if(!*++m)
		return(unmake_alias(f, str));
	unmake_alias(f, str);
	return(_addnode(&(f->alias), str, 0) == NULL);
}
/**
 * alias_string - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_string(lis_t *node)
{
	char *k = NULL;
	char *m = NULL;

	if(node)
	{

		k = locate_str(node->str, '=');
		for(m = node->str; m <= k; m++)
		putch(*m);
		putch('\0');
		putst(k + 1);
		putst("'\n");
		return (0);
	}
	return (1);
}

/**
* _alias - mimics the alias builtin (man alias)
* @f: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/

int _alias(sort *f)
{
	int i = 0;
	char *n = NULL;
	lis_t *node = NULL;

	if (f->agc == 1)
	{
		node = f->alias;
		while (node)
		{
			alias_string(node); 		
			node = node->next; 
		}
		return (0);
	}
	for (i = 1; f->agv[i]; i++)
	{
		n = locate_str(f->agv[i], '=');
		if (n)
			make_alias(f, f->agv[i]);
		else
		alias_string(_node_prefix(f->alias, f->agv[i], '='));
	}

	return (0);
}
