#include "shell.h"
/**
* cha_buff - buffers chained commands
* @info: parameter struct
* @buf: address of buffer
* @len: address of len var
*
* Return: bytes read
*/
ssize_t cha_buff(sort *f, char **buff, size_t *len)
{
	ssize_t r = 0;
	size_t len_k = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, signint);
#if USE_GETLINE
		r = getline(buff, &len_k, stdin);
	#else
		r = _get_line(f, buff, &len_k);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			f->linecount_flag = 1;
			rep_lines(*buff);
		add_list(f, *buff, f->histcount++);
/* if (_strchr(*buf, ';')) is this a command chain? */{
		*len = r;
		f->cmd_buf = buff;
			}
		}
	}
return (r);
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
	static size_t i, j, length;
	ssize_t r = 0;

	char **buf_k = &(f->arg), *p;
	putch(BUF_FLUSH);
	r = cha_buff(f, &buff, &length);
	if (r == -1) /* EOF */
		return (-1);
	if (length) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buff + i; /* get pointer for return */
		ch_chain(f, buff, &j, i, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (_chain(f, buff, &j))
				break;
			j++;
		}
			i = j + 1; /* increment past nulled ';'' */
		if (i >= length) /* reached end of buffer? */
		{
		i = length = 0; /* reset position and length */
		f->cmd_buf_type = CMD_NORM;
		}
		*buf_k = p; /* pass back pointer to current command position */
		return (_strl(p)); /* return length of current command */}
	*buf_k = buff; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}
/**
* read_buffer - reads a buffer
* @info: parameter struct
* @buf: buffer
* @i: size
*
* Return: r
*/
ssize_t read_buffer(sort *f, char *buf, size_t *i)
{
	ssize_t n = 0;
	if (*i)
		return (0);
	n = read(f->readfd, buf, READ_BUF_SIZE);
	if (n >= 0)
		*i = n;
	return (n);
}
/**
* _get_line - gets the next line of input from STDIN
* @f: parameter struct
* @ptr: address of pointer to buffer, preallocated or NULL
* @length: size of preallocated ptr buffer if not NULL
*
* Return: s
*/
int _get_line(sort *f, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
	{
		i = len = 0;
		r = read_buffer(f, buf, &len);
	}
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = locate_str(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _reall(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	if (s)
		_str_cat(new_p, buf + i, k - i);
	else
		str_cp(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
* signint - blocks ctrl-C
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
