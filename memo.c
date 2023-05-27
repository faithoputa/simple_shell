#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * bfree - free a pointer and NULL the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise -1.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free (*ptr);
		*ptr = NULL;
		return (1);
	}
	return (-1);
}
