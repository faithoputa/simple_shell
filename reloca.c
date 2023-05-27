#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * _memset - fill memory with a constant byte
 * @o: the pointer to the memory area
 * @s: the byte to fill *o with
 * @r: the amount of bytes to be filled
 * Return: (o) a pointer to the memory area o
 */
char *_memset(char *o, char s, unsigned int r)
{
	unsigned int g;

	for (g = 0; g < r; g++)
		o[g] = s;
	return (o);
}

/**
 * ffree - freesa string of strings
 * @tt: string of strings
 */
void ffree(char **tt)
{
	char **z = tt;

	if (!tt)
		return;
	while (*tt)
		free(*tt++);
	free(z);
}

/**
 * _realloc - real-locate a block of memory
 * @ptr: pointer to previous mallocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *t;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	t = malloc(new_size);
	if (!t)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		t[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (t);
}
