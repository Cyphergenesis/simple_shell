#include "shell.h"
/*** hsh - main shell loop
* @info: the parameter & return info struct
* @av: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int _hsh(sort *f, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;
	while (r != -1 && builtin_ret != -2)
	{
		_clear(f);
		if (_active(f))
		putst("$ ");
		_write(BUF_FLUSH);
	r = _input(f);
		if (r != -1)
		{
			_info(f, av);
			builtin_ret = _builtin(f);
		if (builtin_ret == -1)
			_find(f);
		}
		else if (_active(f))
			putch('\n');
		release_sort(f, 0);
	}
	_create(f);
	release_sort(f, 1);
	if (!_active(f) && f->status)
		exit(f->status);
	if (builtin_ret == -2)
	{
		if (f->err_num == -1)
			exit(f->status);
		exit(f->err_num);
	}	
	return (builtin_ret);
}
/**
* _builtin - finds a builtin command
* @f: the parameter & return info struct
*
* Return: -1 if builtin not found,
*
0 if builtin executed successfully,*
1 if builtin found but not successful,
*
2 if builtin signals exit()
*/
int _builtin(sort *f)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
	{"exit", _ex_shell},
	{"env", curr_env},
	{"help", _chdirectory},
	{"history", _display_list},
	{"setenv", new_env},
	{"unsetenv", _rem_environ},
	{"cd", _chcd},
	{"alias", _alias},
	{NULL, NULL}
	};
	for (i = 0; builtintbl[i].type; i++)
		if (_strcm(f->argv[0], builtintbl[i].type) == 0)
		{
			f->line_count++;
			built_in_ret = builtintbl[i].func(f);
			break;
		}
	return (built_in_ret);
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
	int i, k;
	f->path = f->argv[0];
	if (f->linecount_flag == 1)
	{
		f->line_count++;
		f->linecount_flag = 0;
	}
	for (i = 0, k = 0; f->arg[i]; i++)
		if (!checks_delim(f->arg[i], " \t\n"))
		k++;
	if (!k)
return;
	path = _path_cmd(f, _get_env(f, "PATH="), f->argv[0]);
	if (path)
	{
		f->path = path;
		_fork(f);
	}
	else
	{
		if ((_active(f) || _get_env(f, "PATH=") || 	
	f->argv[0][0] == '/') && _cmd(f, f->argv[0]))
		_fork(f);
		else if (*(f->arg) != '\n')
		{
			f->status = 127;
			_error(f, "not found\n");
		}
	}
}
/**
* _fork - forks a an exec thread to run cmd
* @info: the parameter & return info struct
*
* Return: void
*/
void _fork(sort *f)
{
	pid_t child_pid;
	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
	if (execve(f->path, f->argv, _environ(f)) == -1)
		{
			release_sort(f, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(f->status));
		if (WIFEXITED(f->status))
		{
			f->status = WEXITSTATUS(f->status);
			if (f->status == 126)
				_error(f, "Permission denied\n");
		}
	}
}
