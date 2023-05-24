#include "shell.h"
/**
* _cmd - determines if a file is an executable command
* @f: the info struct
* @path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int _cmd(sort *f, char *path)
{
	struct stat st;
	(void)f;

	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
* _chars_dup - duplicates characters
* @pstr: the PATH string
* @start: starting index
* @stop: stopping index
*
* Return: pointer to new buffer
*/
char *_chars_dup(char *pstr, int start, int stop)
{
	static char buff[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < stop; i++)
	{
		if (pstr[i] != ':')
			buff[j++] = pstr[i];
		buff[j] = 0;
	}
		return (buff);
}
/**
* _path_cmd - finds this cmd in the PATH string
* @f: the info struct
* @pstr: the PATH string
* @cmd: the cmd to find
*
* Return: full path of cmd if found or NULL
*/
char *_path_cmd(sort *f, char *pstr, char *cmd)
{
	int i = 0, curr_post = 0;
	char *pth;

	if (!pstr)
		return (NULL);
	if ((_strl(cmd) > 2) && start_hay(cmd, "./"))
	{
		if (_cmd(f, cmd))
		return (cmd);
	}
	while (1)
	{
	if (!pstr[i] || pstr[i] == ':')
	{
		pth = _chars_dup(pstr, curr_post, i);
		if (!*pth)
		_strc(pth, cmd); else
	{
		_strc(pth, "/");
		_strc(pth, cmd);
	}
		if (_cmd(f, pth))
		return (pth);
		if (!pstr[i])
	break;
	curr_post = i;
	}
	i++;
	}
	return (NULL);
}
