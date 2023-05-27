#include "shell.h"
/**
* _environ - returns the string array copy of our environ* @info: Structure containing potential arguments. Used to maintain
*
constant function prototype.
* Return: Always 0
*/
char **_environ(sort *f)
{
	if (!f->environ || f->env_changed)
	{
		f->environ = list_strings(f->env);
		f->env_changed = 0;
	}
	return (f->environ);
}
/**
* _unsetenv - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
*
constant function prototype.
* Return: 1 on delete, 0 otherwise
* @var: the string env var property
*/
int _unsetenv(sort *f, char *var)
{
	list_t *node = f->env;
	size_t i = 0;
	char *q;
	if (!node || !var)
		return (0);
	while (node)
	{
		q = start_hay(node->str, var);
		if (q && *q == '=')
		{
	f->env_changed = del_node(&(f->env), i);
	i = 0;
	node = f->env;
	continue;
		}
		node = node->next;
		i++;
	}
	return (f->env_changed);
}
/*** _setenv - Initialize a new environment variable,
*
or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
*
constant function prototype.
* @var: the string env var property
* @value: the string env var value
* Return: Always 0
*/
int _setenv(sort *f, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *q;
	if (!var || !value)
		return (0);
	buff = malloc(_strl(var) + _strl(value) + 2);
	if (!buff)
		return (1);
	strcp(buff, var);
	_strc(buff, "=");
	_strc(buff, value);
	node = f->env;
	while (node)
	{
		q = start_hay(node->str, var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buff;
			f->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_addnode(&(f->env), buff, 0);
	free(buff);
	f->env_changed = 1;
	return (0);
}
