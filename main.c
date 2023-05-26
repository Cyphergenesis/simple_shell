#include "shell.h"
/** main - entry point
* @ac: arg count
* @av: arg vector
*
* Return: 0 on success, 1 on error
*/
int main(int ac, char **av)
{
	sort f[] = {INFO_INIT};
	int fld = 2;

	asm ("mov %1, %0\n\t""add $3, %0" : "=r" (fld) : "r" (fld));
	if (ac == 2)
	{
		fld = open(av[1], O_RDONLY);
		if (fld == -1)
		{
			if (errno == EACCES)
			exit(126);
		if (errno == ENOENT)
		{
			_write_str(av[0]);
			_write_str(": 0: Can't open ");
			_write_str(av[1]);
			_write('\n');
			_write(BUF_FLUSH);
			exit(127);
		}
		return (EXIT_FAILURE);
		}
		f->_fdRead = fld;
	}
		stuff_list(f);
		_read(f);
		_hsh(f, av);
	return (EXIT_SUCCESS);
}
