#include "shell.h"
#include <errno.h>
#include <stdlib.h>

/**
 * main -  the entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 1 on success, -1 on error
 */
int main(int ac, char **av)
{ /* (void)INFO_INIT, (VOID)O_RDONLY */
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = (av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eputs(av[0]);
				eputs(": 0: Can't open ");
				eputs(av[1]);
				eputchar('\n');
				eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);	
	hsh(info, av);
	return (EXIT_SUCCESS);
}
