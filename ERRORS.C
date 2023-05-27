#include "shell.h"

/**
 *_eput- print an input string
  * Return: Nothing
 */
void _eputs(char *str)
{
        int k = 0;

        if (!str)
                return;
        while (str[k] != '\0')
        {
                _eputchar(str[k]);
                k++;
        }
}

/**
 * _eputchar - write the character a to stderr
 * @a: The character to print
 * Return: On success 1.
 * On error,  return -1, and errno is set appropriately.
 */
int _eputchar(char a)
{
        static int k;
        static char buf[WRITE_BUF_SIZE];

        if (a == BUF_FLUSH || k >= WRITE_BUF_SIZE)
        {
                write(2, buf, k);
                k = 0;
        }
        if (a != BUF_FLUSH)
                buf[k++] = a;
        return (1);
}                        }

/**
 * _addfd - writes the character a to given fd
 * @a: The character to print
 * @fd: The file descriptor to write.
 * Return: On success 1.
 * On error, return -1, and errno is set appropriately.
 */
int _addfd(char a, int fd)
{
        static int k;
        static char buf[WRITE_BUF_SIZE];

        if (a == BUF_FLUSH || k >= WRITE_BUF_SIZE)
        {
                write(fd, buf, k);
                k = 0;
        }
        if (a != BUF_FLUSH)
                buf[k++] = a;
        return (1);
}

/**
 *_addfd - print an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{                                            {
        int k = 0;

        if (!str)
                return (0);
        while (*str)
        {
                k += _addfd(*str++, fd);
        }
        return (k);
}
