#include "shell.h"
/**
* _init - initializes info_t struct
* @f: struct address
*/
void _clear(sort *f)
{
	f->ag = NULL;
	f->agv = NULL;
	f->pth = NULL;
	f->agc = 0;
}
/**
* init_sort - initializes info_t struct
* @sort: struct address
* @arv: argument vector
*/
void _info(sort *f, char **av)
{
	int i = 0;

	f->_name = av[0];
	if (f->agv)
	{
		f->agv = tow(f->ag, "\t");
		if (!f->agv)
		{
			f->agv = malloc(sizeof(char *) * 2);
			if (f->agv)
			{
				f->agv[0] = _dup(f->ag);
				f->agv[1] = NULL;

			}

		}
	for (i = 0; f->agv && f->agv[i]; i++);
	f->agc = i;

	rep_alia(f);
	rep_var(f);
	}

}

/**
* free_info - frees info_t struct fields
* @f: struct address* @all: true if freeing all fields
* @a: true if all fields
*/
void release_sort(sort *f, int a)
{
	_free_str(f->agv);
	f->agv = NULL;
	f->pth = NULL;
	if (a)
	{
		if (!f->cmd_buff)
			free(f->ag);
		if (f->env)
			distro_list(&(f->env));
		if (f->history)
			distro_list(&(f->history));
		if (f->alias)
			distro_list(&(f->alias));
		_free_str(f->environ);
			f->environ = NULL;
		_free((void **)f->cmd_buff);
		if (f->_fdRead > 2)
		close(f->_fdRead);
		putch(BUF_FLUSH);

	}

}
