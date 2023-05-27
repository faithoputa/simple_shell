#include "shell.h"

/**
 * is_cmd - check  if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, -1 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (-1);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (-1);
}

/**
 * dup_chars - duplicate characters
 * @pathstr: the PATH string
 * @start: starting index
 * @quit: quit  index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int quit)
{
	static char buf[1024];
	int g = 0, w = 0;

	for (w = 0, g = start; g < quit; g++)
		if (pathstr[g] != ':')
			buf[w++] = pathstr[g];
	buf[w] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int g = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[g] || pathstr[g] == ':')
		{
			path = dup_chars(pathstr, curr_pos, g);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[g])
				break;
			curr_pos = g;
		}
		g++;
	}
	return (NULL);
}
