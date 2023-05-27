#include "shell.h"
/**
* curr_env - prints the current environment
* @info: Structure containing potential arguments. Used to maintain
*
constant function prototype.
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
* @name: env var name
*
* Return: the value
*/
char *_get_env(sort *f, const char *name)
{

	list_t *node = f->env;
	char *q;
	while (node)
	{
		q = start_hay(node->str, name);
		if (q && *q)
		return (q);
		node = node->next;
	}
		return (NULL);
}
/**
* new_env - Initialize a new environment variable,
*
or modify an existing one
* @f: Structure containing potential arguments. Used to maintain
*
constant function prototype.
* Return: Always 0
*/
int new_env(sort *f)
{
	if (f->argc != 3)
	{
		_write_str("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(f, f->argv[1], f->argv[2]))
		return (0);
	return (1);
}
/**
* _rem_environ- Remove an environment variable
* @f: Structure containing potential arguments. Used to maintain
*
constant function prototype.
* Return: Always 0
*/
int _rem_environ(sort *f)
{
	int i;

	if (f->argc == 1)
	{
		_write_str("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= f->argc; i++)
		_unsetenv(f, f->argv[i]);
	return (0);
}
/**
* populate_env_list - populates env linked list
* @f: Structure containing potential arguments. Used to maintain
*
constant function prototype.
* Return: Always 0
*/
int stuff_list(sort *f)
{
	list_t *node = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		_addnode(&node, environ[k], 0);
	f->env = node;
	return (0);
}
