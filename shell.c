#include "shell.h"

/** _hsh - main shell loop
  * @f: the parameter & return info struct
  * @av: the argument vector from main()
  *
  * Return: 0 on success, 1 on error, or error code
  */
int _hsh(sort *f, char **av)
{
	ssize_t m = 0;
	int built = 0;

	while (m != -1 && built != -2)
	{
		_clear(f);
		if (_active(f))
		putst("$ ");
		_write(BUF_FLUSH);
	m = _input(f);
	if (m != -1)
	{
		_info(f, av);
		built = _builtin(f);
		if (built == -1)
		_find(f);
	}

	else if (_active(f))
	putch('\n');
	release_sort(f, 0);
	}
		_create(f);
		release_sort(f, 1);
	if (!_active(f) && f->_stat)
	exit(f->_stat);
		if (built == -2)
	{
		if (f->_num == -1)
		exit(f->_stat);
		exit(f->_num);
	}
	return (built);
}
/**
* _builtin - finds a builtin command
* @f: the parameter & return info struct
*
* Return: -1 if builtin not found,
* if builtin executed successfully,*
* if builtin found but not successful,
* if builtin signals exit()
*/
int _builtin(sort *f)
{
	int i, built = -1;
	buil_tab b[] = {
		{"exit", _ex_shell},
		{"env", curr_env},
		{"help", _chdirectory},
		{"history", _display_list},
		{"setenv", new_env},
		{"unsetenv", _rem_environ},
		{"cd", _chcd},
		{"alias", _alias},
		{NULL, NULL}};
	for (i = 0; b[i].type; i++)
	if (_strcm(f->argv[0], b[i].type) == 0)
	{
		f->line_count++;
		built = b[i].func(f);
		break;
	}
	return (built);
}
/**
* _find - finds a command in PATH
* @f: the parameter & return info struct
*
* Return: void
*/
void _find(sort *f)
{
	char *path = NULL;
	int i, j;

	f->path = f->argv[0];
	if (f->line_flag == 1)
	{
		f->line_count++;
		f->line_flag = 0;
	}
	for (i = 0, j = 0; f->arg[i]; i++)
		if (!checks_delim(f->arg[i], " \t\n"))
			j++;
	if (!j)
		return;
	path = _path_cmd(f, _get_env(f, "PATH="), f->argv[0]);
		if (path)
		{
			f->path = path;
			_fork(f);
		}
		else
		{
	if ((_active(f) || _get_env(f, "PATH=")
	|| f->argv[0][0] == '/') && _cmd(f, f->argv[0]))
		_fork(f);

		else if (*(f->arg) != '\n')
		{
			f->_stat = 127;
			_error(f, "not found\n");
		}
		}
}

/**
* _fork - forks a an exec thread to run cmd
* @f: the parameter & return info struct
*
* Return: void
*/
void _fork(sort *f)
{
	pid_t pid;
	pid = fork();

	if (pid == -1)
	{
		perror("Error:");
		return;
	}
	if (pid == 0)
	{
	if (execve(f->path, f->argv, _environ(f)) == -1)
		{
		release_sort(f, 1);
		if (errno == EACCES)
		exit(126);
		exit(1);
	}
	else
	{
		wait(&(f->_stat));
		if (WIFEXITED(f->_stat))
		{
			f->_stat = WEXITSTATUS(f->_stat);
			if (f->_stat == 126)
			_error(f, "Permission denied\n");
		}
	}
	}

}

