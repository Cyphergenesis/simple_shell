#include "shell.h"
/**
* cha_buff - buffers chained commands
* @f: parameter struct
* @buff: address of buffer
* @length: address of len var
*
* Return: bytes read
*/
ssize_t cha_buff(sort *f, char **buff, size_t *length)
{
	ssize_t n  = 0;
	size_t en_p = 0;

	if (!*length)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, signint);
		
		n = getline(buff, &en_p, stdin);

		n = _get_line(f, buff, &en_p);

		if (n > 0)
		{
			if ((*buff)[n - 1] == '\n')
			{
				(*buff)[n - 1] = '\0';
				n--;
			}
			f->line_flag = 1;
			rep_lines(*buff);
			add_list(f, *buff, f->_count_num++);
			{
			*length = n;
			f->cmd_buff = buff;
			}

		}


	}

	return (n);
}

/**
* _input - gets a line minus the newline
* @f: parameter struct
*
* Return: bytes read
*/
ssize_t _input(sort *f)
{
	static char *buff;
	static size_t i, k, len;
	ssize_t n = 0;

	char **buf_c = &(f->arg), *v;

	putch(BUF_FLUSH);
	n = cha_buff(f, &buff, &len);

	if (n == -1)
		return (-1);
	if (len)
	{
		k = i;
		v = buff + i;

		ch_chain(f, buff, &k, i, len);
		while (k < len)
		{
			if (_chain(f, buff, &k))
				break;
			k++;
		}

		i = k + 1;

		if (i >= len)
		{
			i = len = 0;
			f->cmd_type = CMD_NORM;
		}
	*buf_c = v;
	return (_strl(v));

	}

	*buf_c = buff;
	return (n);
}

/**
* read_buffer - reads a buffer
* @f: parameter struct
* @buff: buffer
* @n: size
*
* Return: r
*/
ssize_t read_buffer(sort *f, char *buff, size_t *n)
{
	ssize_t j = 0;

	if (*n)
		return (0);
	j = read(f->_fdRead, buff, READ_BUF_SIZE);
	if (j >= 0)
		*n = j;
	return (j);
}

/**
* _get_line - gets the next line of input from STDIN
* @sort: parameter struct
* @ptr: address of pointer to buffer, preallocated or NULL
* @len: size of preallocated ptr buffer if not NULL
*
* Return: s
*/
int _get_line(sort *f, char **ptr, size_t *len)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, length;
	size_t w;
	ssize_t n = 0, m = 0;

	char *q = NULL, *new = NULL;
	char *c;

	q = *ptr;
	if (q && len)
		m = *len;
	if (i == length)
	{
		i = length = 0;
		n = read_buffer(f, buff, &length);
	}
	if (n == -1 || (n == 0 && length == 0))
		return (-1);

	c = locate_str(buff + i, '\n');
	w = c ? 1 + (unsigned int)(c - buff) : length;
	new = _reall(q, m, m ? m + w : w + 1);
	if (!new)
		return (q ? free(q), -1 : -1);
	if (m)
		_str_cat(new, buff + i, w - i);
	else
		str_cp(new, buff + i, w - i + 1);

	m += w - i;
	i = w;
	q = new;

	if (len)
		*len = m;

	*ptr = q;
	return (m);
}
/**
* _signint - blocks ctrl-C
* @sig_num: the signal number
*
* Return: void
*/
void signint(__attribute__((unused))int sig_num)
{

	putst("\n");
	putst("$ ");
	putch(BUF_FLUSH);
}
