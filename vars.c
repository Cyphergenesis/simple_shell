#include "shell.h"
/**
* _chain - test if current char in buffer is a chain delimeter
* @f: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
*
* Return: 1 if chain delimeter, 0 otherwise
*/
int _chain(sort *f, char *buf, size_t *p)
{
	size_t j = *p;
	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		f->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		f->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		f->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}/**
* ch_chain - checks we should continue chaining based on last status
* @f: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
* @i: starting position in buf
* @len: length of buf
*
* Return: Void
*/
void ch_chain(sort *f, char *buff, size_t *p, size_t i, size_t len)
{
	size_t h = *p;
	if (f->cmd_buf_type == CMD_AND)
	{
		if (f->status)
		{
			buff[i] = 0;
			h = len;
		}
	}
		if (f->cmd_buf_type == CMD_OR)
		{
			if (!f->status)
			{
				buff[i] = 0;
				h = len;
			}
		}
			*p = h;
}
/**
* rep_alias - replaces an aliases in the tokenized string
* @f: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int rep_alia(sort *f)
{
	int i;
	list_t *node;
	char *p;
	for (i = 0; i < 10; i++)
	{
	node = _node_prefix(f->alias, f->argv[0], '=');
	if (!node)
	return (0);
		free(f->argv[0]);
		p = locate_str(node->str, '=');
	if (!p)
		return (0);
	p = _dup(p + 1);
	if (!p)
	return (0);
	f->argv[0] = p;
}
return (1);
}
/**
* rep_var- replaces vars in the tokenized string
* @f: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int rep_var(sort *f)
{
	int i = 0;
	list_t *node;
	for (i = 0; f->argv[i]; i++)
	{
	if (f->argv[i][0] != '$' || !f->argv[i][1])
	continue;
		if (!_strcm(f->argv[i], "$?"))
		{
			rep_str(&(f->argv[i]),
			_dup(con_num(f->status, 10, 0)));
			continue;
		}
	if (!_strcm(f->argv[i], "$$"))
	{
		rep_str(&(f->argv[i]),
		_dup(con_num(getpid(), 10, 0)));
		continue;
	}
	node = _node_prefix(f->env, &f->argv[i][1], '=');
	if (node)
	{
	rep_str(&(f->argv[i]), _dup(locate_str(node->str, '=') + 1));
	continue;
	}
	rep_str(&f->argv[i], _dup(""));
	}
return (0);
}
/**
* rep_str - replaces string
* @old: address of old string
* @new: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int rep_str(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
return (1);
}
