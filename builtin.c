#include "shell.h"
/**
* _ex_shell - exits the shell
* @f: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: exits with a given exit status
* (0) if info.argv[0] != "exit"
*/
int _ex_shell(sort *f)
{
	int ex_check;

	if (f->argv[1]) /* If there is an exit arguement */
	{
		ex_check = con_str(f->argv[1]);
		if (ex_check == -1)
		{
			f->status = 2;
			_error(f, "Illegal number: ");
			_write_str(f->argv[1]);
			_write('\n');
			return (1);
		}
		f->err_num = con_str(f->argv[1]);
		return (-2);
	}
	f->err_num = -1;
	return (-2);
}
/**
* _chcd- changes the current directory of the process
* @f: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _chcd(sort *f)
{
	char *ch, *dir, buffer[1024];
	int _chdir;

	ch = getcwd(buffer, 1024);
	if (!ch)
		putst("TODO: >>getcwd failure emsg here<<\n");
	if (!f->argv[1])
	{
		dir = _get_env(f, "HOME=");
		if (!dir)
			_chdir = /* TODO: what should this be? */
			chdir((dir = _get_env(f, "PWD=")) ? dir : "/");
		else
			_chdir = chdir(dir);
	}
	else if (_strcm(f->argv[1], "-") == 0)
	{
	if (!_get_env(f, "OLDPWD="))
		{
		putst(ch);
		putch('\n');
	return (1);
		}
		putst(_get_env(f, "OLDPWD=")), putch('\n');
		_chdir = /* TODO: what should this be? */
		chdir((dir = _get_env(f, "OLDPWD=")) ? dir : "/");
		}
	else
	_chdir = chdir(f->argv[1]);
	if (_chdir == -1)
	{
	_error(f, "can't cd to ");
	_write_str(f->argv[1]), _write('\n');
	}
	else
	{
	_setenv(f, "OLDPWD", _get_env(f, "PWD="));
	_setenv(f, "PWD", getcwd(buffer, 1024));
	}
return (0);
}
/**
* _chdirectory - changes the current directory of the process
* @f: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _chdirectory(sort *f)
{
	char **arr;
	arr = f->argv;
	putst("help call works. Function not yet implemented \n");
	if (0)
	putst(*arr);
return (0);
}
