#include "shell.h"
/**
* _clear - initializes info_t struct
* @info: struct address
*/
void _clear(sort *f)
{
	f->arg = NULL;
	f->argv = NULL;
	f->path = NULL;
	f->argc = 0;
}
/**
* _info - initializes info_t struct
* @f struct address
* @av: argument vector
*/
void _info(sort *f, char **av)
{
	int i = 0;
	f->fname = av[0];
	if (f->arg)
	{
		f->argv = tow(f->arg, " \t");
		if (!f->argv)
		{
			f->argv = malloc(sizeof(char *) * 2);
			if (f->argv)
			{
				f->argv[0] = _dup(f->arg);
				f->argv[1] = NULL;
			}
		}
		for (i = 0; f->argv && f->argv[i]; i++);
		f->argc = i;
		rep_alia(f);
		rep_var(f);
	}
}
/**
* release_sort- frees info_t struct fields
* @f: struct address* @all: true if freeing all fields
*/
void release_sort(sort *f, int a)
{
	_free_str(f->argv);
	f->argv = NULL;
	f->path = NULL;
	if (a)
	{
		if (!f->cmd_buf)
			free(f->arg);
		if (f->env)
			distro_list(&(f->env));
		if (f->history)
			distro_list(&(f->history));
		if (f->alias)
			distro_list(&(f->alias));
		_free_str(f->environ);
		f->environ = NULL;
		_free((void **)f->cmd_buf);
		if (f->readfd > 2)
			close(f->readfd);
		putch(BUF_FLUSH);
	}
}
