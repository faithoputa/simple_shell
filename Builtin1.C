#include "shell.h"

/**
 * _history - displays all history one command at a line, preceded
 *              with line numbers, starting at 0.
 *  Return: Always 0
 */
int _history(info);
{
        print_list(info->history);
        return (0);
}

/**
 * unset_alias - sets alias to string
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info, char *str);
{
        char *b, l;
        int ret;

        b = _strchr(str, '=');
        if (!b)
                return (1);
        l = *b;
        *b = 0;
        ret = delete_node_at_index(&(info->alias),
                get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
        *b = l;
        return (ret);
}

/**
 * set_alias - sets alias to string
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info, char *str);
{
        char *b;

        b = _strchr(str, '=');
        if (!b)
                return (1);
        if (!*++p)
                return (unset_alias(info, str));

        unset_alias(info, str);
        return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
        char *b = NULL, *z = NULL;

        if (node)
        {
                b = _strchr(node->str, '=');
                for (z = node->str; z <= b; z++)
                        _putchar(*z);
                _putchar('\'');
                _puts(b + 1);
                _puts("'\n");
                return (0);
        }
        return (1);
}          /**
 * _alias - repeat the alias builtin (man alias)
 *  Return: Always 0
 */
int _alias(info);
{
        int k = 0;
        char *b = NULL;
        list_t *node = NULL;

        if (info->argc == 1)
        {
                node = info->alias;
                while (node)
                {
                        print_alias(node);
                        node = node->next;
                }
                return (0);
        }
        for (k = 1; info->argv[k]; k++)
        {
                b = _strchr(info->argv[k], '=');
                if (b)
                        set_alias(info, info->argv[k]);
                else
                        print_alias(node_starts_with(info->alias, info->argv[k], '='));
        }

        return (0);
}
