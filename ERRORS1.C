#include "shell.h"

/**
 * _erratoi - convert a string to an integer
 * @x: the string to be converted
 * Return: 0 if no numbers in string, otherwise -1 on error  converted numbers
 */
int _erratoi(char *x)
{
        int k = 0;
        unsigned long int result = 0;

        if (*x == '+')
                x++;  
/* TODO: why does this make main return 255? */
        for (k = 0; x[k] != '\0'; k++)
        {
                if (x[k] >= '0' && x[k] <= '9')
                {
                        result *= 10;
                        result += (x[k] - '0');
                        if (result > INT_MAX)
                                return (-1);
                }
                else
                        return (-1);
        }
        return (result);
}

/**
 * print_error - prints an error message
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, otherwise -1 on converted numbe
 */
void print_error(info_t *info, char *estr)
{
        _eputs(info->fname);
        _eputs(": ");
        print_d(info->line_count, STDERR_FILENO);
        _eputs(": ");              _eputs(info->argv[0]);
        _eputs(": ");
        _eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
        int (*__putchar)(char) = _putchar;
        int k, count = 0;
        unsigned int abs, current;

        if (fd == STDERR_FILENO)
                __putchar = _eputchar;
        if (input < 0)
        {
                abs = -input;
                __putchar('-');
                count++;
        }
        else
                abs = input;
        current = abs;
        for (k = 1000000000; k > 1; k /= 10)
        {
                if (abs / k)
                {
                        __putchar('0' + current / k);
                        count++;
                }  /**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
        static char *array;
        static char buffer[50];
        char sign = 0;
        char *ptr;
        unsigned long a = num;

        if (!(flags & CONVERT_UNSIGNED) && num < 0)
        {
                a = -num;
                sign = '-';

        }
        array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
        ptr = &buffer[49];
        *ptr = '\0';

        do      {
                *--ptr = array[a % base];
                a /= base;
        } while (a != 0);

        if (sign)
                *--ptr = sign;
        return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */                   void remove_comments(char *buf)
{
        int k;

        for (k = 0; buf[k] != '\0'; k++)
                if (buf[k] == '#' && (!k || buf[k - 1] == ' '))
                {
                        buf[k] = '\0';
                        break;
                }
}
