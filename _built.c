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
	int exitcheck;

	if (f->agv[1])
	{
		exitcheck = con_str(f->agv[1]);
		if (exitcheck == -1)
		{
			f->_stat = 2;
			_error(f, "illegal number:");
			_write_str(f->agv[1]);
			_write('\n');
			return (1);
		}
		f->_num = con_str(f->agv[1]);
		return (-2);
	}
	f->_num = -1;
	return (-2);

}
/**
* _chcd - changes the current directory of the process
* @f: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _chcd(sort *f)
{
	char *s, *set, buff[1024];
	int _chdir;

	s = getcwd(buff, 1024);
	if (!s)
		putst("error message\n");
	if (!f->agv[1])
	{
		set = _get_env(f, "HOME=");
		if (!set)

	_chdir = chdir((set = _get_env(f, "PWD")) ? set : "/");
		else
			_chdir = chdir(set);

	}
	else if (_strcm(f->agv[1], "-") ==  0)
	{
		if (!_get_env(f, "OLDPWD"))
		{
			putst(s);
			putch('\n');
		return (1);
		}
	putst(_get_env(f, "OLDPWD=")), putch('\n');
	_chdir = chdir((set = _get_env(f, "OLDPWD")) ? set : "/");
	}
	else
		_chdir  = chdir(f->agv[1]);
	if  (_chdir == -1)
	{
		_error(f, "wrong command");
		_write_str(f->agv[1]), _write('\n');
	}
	else
	{
		init_env(f, "OLDPWD", _get_env(f, "PWD="));
		init_env(f, "PWD", getcwd(buff, 1024));
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
	char **ag;

	ag = f->agv;
	putst("Not yet implemented\n");
	if (0)

		putst(*ag);
	return (0);
}
