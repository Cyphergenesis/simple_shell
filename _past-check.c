#include "shell.h"
/**
* gets_file - gets the history file
* @f: parameter struct
* Return: allocated string containg history file
*/
char *gets_file(sort *f)
{
	char *buff, *dirr;

	dirr = _get_env(f, "HOME=");
	if (!dirr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strl(dirr) + _strl(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	strcp(buff, dirr);
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
	ssize_t fld;
	char *f_name = gets_file(f);
	lis_t *node = NULL;

	if (!f_name)
		return (-1);
	fld = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);

	if (fld == -1)
		return (-1);
	for (node = f->history; node; node = node->next)
	{
		_print_string(node->str, fld);
		write_fd('\n', fld);
	}
	write_fd(BUF_FLUSH, fld);
	close(fld);

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
	ssize_t fld, read_len, f_size = 0;
	int i, las = 0, line_count = 0;
	struct stat st;
	char *buff = NULL, *f_name = gets_file(f);

	if (!f_name)
		return (0);

	fld = open(f_name, O_RDONLY);
	free(f_name);
	if (fld == -1)
		return (0);

	if (!fstat(fld, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_size + 1));
	if (!buff)
		return (0);
	read_len = read(fld, buff, f_size);
	buff[f_size] = 0;
	if (read_len <= 0)
		return (free(buff), 0);
	close (fld);
	for (i = 0; i < f_size; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			add_list(f, buff + las, line_count++);
			las = i + 1;
		}
	if (las != i)
	{
		add_list(f, buff + las, line_count++);
		free(buff);
	f->_count_num = line_count;
	}
	while (f->_count_num-- >= HIST_MAX)
		del_node(&(f->history), 0);
	renum_link(f);
	return (f->_count_num);
}
/**
* add_list - adds entry to a history linked list
* @f: Structure containing potential arguments. Used to maintain
* @buff: buffer
* @line_count: the history linecount, histcount
*
* Return: Always 0
*/
int add_list(sort *f, char *buff, int line_count)
{
	lis_t *node = NULL;

	if (f->history)
		node = f->history;
	_addnode(&node, buff, line_count);

	if (!f->history)
		f->history = node;
	return (0);
}
/**
* renum_link - renumbers the history linked list after changes
* @f: Structure containing potential arguments. Used to maintain
* Return: the new histcount
*/
int renum_link(sort *f)
{
	lis_t *node = f->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (f->_count_num = i);
}
