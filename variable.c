#include "shell.h"
/**
* _chain - test if current char in buffer is a chain delimeter
* @f: the parameter struct
* @buff: the char buffer
* @cur: address of current position in buf
*
* Return: 1 if chain delimeter, 0 otherwise
*/
int _chain(sort *f, char *buff, size_t *cur)
{
	size_t g = *cur;
	if (buff[g] == '|' && buff[g + 1] == '|')
	{
		buff[g] = 0;
		g++;
		f->cmd_type = CMD_OR;
	}
	else if (buff[g] == '&' && buff[g + 1] == '&')
	{
		buff[g] = 0;
		g++;
		f->cmd_type = CMD_AND;
	}
	else if (buff[g] == ';') /* found end of this command */
	{
		buff[g] = 0; /* replace semicolon with null */
		f->cmd_type = CMD_CHAIN;
	}
	else
		return (0);
	*cur = g;
return (1);
}

/**
* check_chain - checks we should continue chaining based on last status
* @f: the parameter struct
* @buff: the char buffer
* @q: address of current position in buf
* @i: starting position in buf
* @len: length of buf
*
* Return: Void
*/
void ch_chain(sort *f, char *buff, size_t *q, size_t i, size_t len)
{
	size_t g = *q;
	if (f->cmd_type == CMD_AND)
	{
		if (f->_stat)
		{
			buff[i] = 0;
			g = len;
		}
	}
	if (f->cmd_type == CMD_OR)
	{
		if (!f->_stat)
		{
			buff[i] = 0;
			g = len;
		}
	}
	*q = g;
}

/**
* rep_alia - replaces an aliases in the tokenized string
* @f: the parameter struct
* Return: 1 if replaced, 0 otherwise
*/
int rep_alia(sort *f)
{
	int i;
	lis_t *node;
	char *q;
	for (i = 0; i < 10; i++)
	{
		node = _node_prefix(f->alias, f->agv[0], '=');
		if (!node)
			return (0);
		free(f->agv[0]);
	q = locate_str(node->str, '=');
		if (!q)
			return (0);
		q = _dup(q + 1);
		if (!q)
			return (0);
		f->agv[0] = q;
	}
	return (1);
}

/**
* rep_var - replaces vars in the tokenized string
* @f: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int rep_var(sort *f)
{
	int i = 0;
	lis_t *node;

	for (i = 0; f->agv[i]; i++)
	{
		if (f->agv[i][0] != '$' || !f->agv[i][1])
			continue;
		if (!_strcm(f->agv[i], "$?"))
		{
			rep_str(&(f->agv[i]),
		_dup(con_num(f->_stat, 10, 0)));
			continue;
		}
		if (!_strcm(f->agv[i], "$$"))
		{
			rep_str(&(f->agv[i]),
			_dup(con_num(getpid(), 10, 0)));

			continue;
		}
		node = _node_prefix(f->env, &f->agv[i][1], '=');
		if (node)
		{
			rep_str(&(f->agv[i]),
			_dup(locate_str(node->str, '=') + 1));
			continue;
		}

		rep_str(&f->agv[i], _dup(""));
	}
	return (0);
}
/**
* rep_str - replaces string
* @oldstr: address of old string
* @newstr: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int rep_str(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}

