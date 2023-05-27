#include "shell.h"

/**
 * is_chain - To test ifvthe current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, -1 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t w = *p;

	if (buf[w] == '|' && buf[w + 1] == '|')
	{
		buf[w] = 0;
		w++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[w] == '&' && buf[w + 1] == '&')
	{
		buf[w] = 0;
		w++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[w] == ';') /* found end of this command */
	{
		buf[w] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (-1);
	*p = w;
	return (1);
}

/**
 * check_chain - To check if  we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @g: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t g, size_t len)
{
	size_t w = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[g] = 0;
			w = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[g] = 0;
			w = len;
		}
	}

	*p = w;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, -1 otherwise
 */
int replace_alias(info_t *info)
{
	int g;
	list_t *node;
	char *p;

	for (g = 0; g < 10; g++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, -1 otherwise
 */
int replace_vars(info_t *info)
{
	int g = 0;
	list_t *node;

	for (g = 0; info->argv[g]; g++)
	{
		if (info->argv[g][0] != '$' || !info->argv[g][1])
			continue;

		if (!_strcmp(info->argv[g], "$?"))
		{
			replace_string(&(info->argv[g]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[g], "$$"))
		{
			replace_string(&(info->argv[g]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[g][1], '=');
		if (node)
		{
			replace_string(&(info->argv[g]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[g], _strdup(""));

	}
	return (-1);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, -1 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
