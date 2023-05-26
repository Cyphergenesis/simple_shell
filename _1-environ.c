#include "shell.h"
/**
* curr_env - prints the current environment
* @f: Structure containing potential arguments. Used to maintain
*constant function prototype.
* Return: Always 0
*/
int curr_env(sort *f)
{
	write_str(f->env);
	return (0);
}
/**
* _get_env - gets the value of an environ variable
* @f: Structure containing potential arguments. Used to maintain
* @u_name: env var name
* Return: the value
*/
char *_get_env(sort *f, const char *u_name)
{
	lis_t *node = f->env;
	char *m;

	while (node)
	{
		m = start_hay(node->str, u_name);
		if (m && *m)
			return (m);
		node = node->next;
	}
	return (NULL);
}

/**
*new_env - Initialize a new environment variable or modify an existing one
*@f: Structure containing potential arguments. Used to maintain
*constant function prototype.
* Return: Always 0
*/
int new_env(sort *f)
{
	if (f->agc != 3)
	{
		_write_str("wrong number\n");
		return (1);
	}
	if (init_env(f, f->agv[1], f->agv[2]))
		return (0);
	return (1);
}
/**
* _rem_environ - Remove an environment variable
* @f: Structure containing potential arguments. Used to maintain
*constant function prototype.
* Return: Always 0
*/
int _rem_environ(sort *f)
{
	int i;

	if (f->agc == 1)
	{
		_write_str("few arguments\n");
		return (1);
	}

	for (i = 1; i <= f->agc; i++)
		_remove_env(f, f->agv[i]);
	return (0);
}
/**
* stuff_list - populates env linked list
* @f: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int stuff_list(sort *f)
{
	lis_t  *node = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		_addnode(&node, environ[k], 0);
	f->env = node;
	return (0);
}
