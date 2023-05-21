#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
        ssize_t z = 0;
        size_t len_b = 0;

        if (!len) / if nothing left in the buffer, fill it */
        {
                /*bfree((void **)info->cmd_buf);*/
                free(*buf);
                *buf = NULL;
                signal(SIGINT, sigintHandler);
#if USE_GETLINE
                z = getline(buf, &len_b, stdin);
#else
                z = _getline(info, buf, &len_b);
#endif
                if (z > 0)
                {
                        if ((*buf)[z - 1] == '\n')
                        {
                                (buf)[z - 1] = '\0'; / remove trailing newline */
                                z--;
                        }
                        info->linecount_flag = 1;
                        remove_comments(*buf);
                        build_history_list(info, *buf, info->histcount++);
                        /* if (_strchr(*buf, ';')) is this a command chain? */
                        {
                                *len = z;
                                info->cmd_buf = buf;
                        }
                }
        }                                             return (z);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
        static char buf; / the ';' command chain buffer */
        static size_t  k, m, len;
        ssize_t  z = 0;
        char **buf_p = &(info->arg), *p;

        _putchar(BUF_FLUSH);
        z = input_buf(info, &buf, &len);
        if (z == -1) /* EOF */
                return (-1);
        if (len)        /* we have commands left in the chain buffer */
        {
                m = k; /* init new iterator to current buf position */
                p = buf + k; /* get pointer for return */

                check_chain(info, buf, &m, k, len);
                while (m < len) /* iterate to semicolon or end */
                {
                        if (is_chain(info, buf, &m))
                                break;
                        m++;
                }

                k = m + 1; /* increment past nulled ';'' */
                if (k >= len) /* reach the end of the buffer? */
                {
                        k = len = 0; /* reset position and length */
                        info->cmd_buf_type = CMD_NORM;
                }

                buf_p = p; / pass back pointer to current command position */
                return (_strlen(p)); /* return length of current command */
        }                           buf_p = buf; / else not a chain, pass back buffer from _getline() */
        return (z); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @k: size
 *
 * Return: z
 */
ssize_t read_buf(info_t *info, char *buf, size_t *k)
{
        ssize_t z = 0;

        if (*k)
                return (0);
        z = read(info->readfd, buf, READ_BUF_SIZE);
        if (z >= 0)
                *k = z;
        return (z);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: x
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
        static char buf[READ_BUF_SIZE];
        static size_t k, len;
        size_t h;
        ssize_t z = 0, x = 0;
        char *b = NULL, *new_b = NULL, *a;

        b = *btr;
        if (b && length)                               
 x = *length;
        if (k == len)
                i = len = 0;

        z = read_buf(info, buf, &len);
        if (z == -1 || (z == 0 && len == 0))
                return (-1);

        a = _strchr(buf + k, '\n');
        h = a ? 1 + (unsigned int)(a - buf) : len;
        new_b = _realloc(b, x, x ? x + h : h + 1);
        if (!new_b) /* MALLOC FAILURE! */
                return (p ? free(p), -1 : -1);

        if (s)
                _strncat(new_b, buf + k, h - k);
        else
                _strncpy(new_b, buf + k, h - k + 1);

        x += h - k;
        k = h;
        b = new_b;

        if (length)
                *length = x;
        *btr = b;
        return (x);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(_attribute_((unused))int sig_num)
{
        _puts("\n");
        _puts("$ ");
        _putchar(BUF_FLUSH);
}
