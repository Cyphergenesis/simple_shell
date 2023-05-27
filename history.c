#include "shell.h"
/**
* gets_file - gets the history file
* @info: parameter struct
*
* Return: allocated string containg history file
*/
char *gets_file(sort *f)
{
	char *buff, *d_ir;
	
	d_ir = _get_env(f, "HOME=");
	if (!d_ir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strl(d_ir) + _strl(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	strcp(buff, d_ir);
	_strc(buff, "/");
	_strc(buff, HIST_FILE);
	return (buff);
}
/**
* _create - creates a file, or appends to an existing file
* @f: the parameter struct
*
* Return: 1 on success, else -1
*/
int _create(sort *f)
{
	ssize_t fd;
	char *file_n = gets_file(f);

	list_t *node = NULL;
	if (!file_n)
		return (-1);
	fd = open(file_n, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_n);
	if (fd == -1)
		return (-1);
	for (node = f->history; node; node = node->next)
	{
		_print_string(node->str, fd);
		write_fd('\n', fd);
	}
	write_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
* _read - reads history from file
* @f: the parameter struct
*
* Return: histcount on success, 0 otherwise
*/
int _read(sort *f)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rd_len, fsize = 0;
	struct stat st;
	char *buff = NULL, *file_n = gets_file(f);

	if (!file_n)
		return (0);
	fd = open(file_n, O_RDONLY);
	free(file_n);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rd_len = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rd_len <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			add_list(f, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		add_list(f, buff + last, linecount++);
	free(buff);
	f->histcount = linecount;
	while (f->histcount-- >= HIST_MAX)
		del_node(&(f->history), 0);
	renum_link(f);
	return (f->histcount);
}
/**
* add_list - adds entry to a history linked list
* @f: Structure containing potential arguments. Used to maintain
* @buf: buffer
* @linecount: the history linecount, histcount
*
* Return: Always 0
*/
int add_list(sort *f, char *buf, int linecount)
{
	list_t *node = NULL;
	if (f->history)
		node = f->history;
	_addnode(&node, buf, linecount);
	if (!f->history)
		f->history = node;
	return (0);
}
/**
* renum_link - renumbers the history linked list after changes
* @f: Structure containing potential arguments. Used to maintain
*
* Return: the new histcount
*/
int renum_link(sort *f)
{
	list_t *node = f->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (f->histcount = i);
}
