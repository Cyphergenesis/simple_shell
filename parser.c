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
}/**
* _chars_dup - duplicates characters
* @pathstr: the PATH string
* @start: starting index
* @stop: stopping index
*
* Return: pointer to new buffer
*/
char *_chars_dup(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;
	
	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}
/**
* _path_cmd - finds this cmd in the PATH string
* @f: the info struct
* @pathstr: the PATH string
* @cmd: the cmd to find
*
* Return: full path of cmd if found or NULL
*/
char *_path_cmd(sort *f, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;
	if (!pathstr)
		return (NULL);
	if ((_strl(cmd) > 2) && start_hay(cmd, "./"))
	{
		if (_cmd(f, cmd))
		return (cmd);
	}
		while (1)
		{
			if (!pathstr[i] || pathstr[i] == ':')
			{
				path = _chars_dup(pathstr, curr_pos, i);
				if (!*path)
					_strc(path, cmd);
				else
				{	
					_strc(path, "/");
					_strc(path, cmd);
				}
			if (_cmd(f, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
			}
			i++;
		}
return (NULL);
}
