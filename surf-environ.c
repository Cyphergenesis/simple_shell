#include "shell.h"
/**
* _environ - returns the string array copy of our environ
*@f: Structure containing potential arguments. Used to maintain
*constant function prototype.
* Return: Always 0
*/
char **_environ(sort *f)
{
	if (!f->environ|| f->_changed_env)
	{
		f->environ = list_strings(f->env);
		f->_changed_env = 0;
	}
	return (f->environ);
}
/**
* _unsetenv - Remove an environment variable
* @f: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: 1 on delete, 0 otherwise
* @v: the string env var property
*/
int _unsetenv(sort *f, char *v)
{
	lis_t *node = f->env;
	size_t i = 0;
	char *q;

	if (!node || !v)
		return (0);

	while (node)
	{
		q = start_hay(node->str, v);
		if (q && *q == '=')
		{
			f->_changed_env = del_node(&(f->env), i);
			i = 0;
			node = f->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (f->_changed_env);
}
/**
 * init_env -Initialize a new environment variable, or modify an exist
 * ing one
 * @f: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @v: the string env var property
 * @val: the string env var value
 * Return: Always 0
 */
int _setenv(sort *f, char *v, char *val)
{
	char *buff = NULL;
	lis_t *node;
	char *q;

	if (!v || !val)
	return (0);
		buff = malloc(_strl(v) + _strl(val) + 2);
	if (!buff)
		return (1);
	strcp(buff, v);
	_strc(buff, "=");
	_strc(buff, val);
	node = f->env;
	while (node)
	{
		q = start_hay(node->str, v);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buff;
			f->_changed_env = 1;
			return (0);
		}
		node = node->next;
	}
	_addnode(&(f->env), buff, 0);
	free(buff);
	f->_changed_env = 1;
	return (0);
}
