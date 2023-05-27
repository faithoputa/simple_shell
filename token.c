#include "shell.h"

/**
 * **strtow -  To splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int g, w, x, c, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (g = 0; str[g] != '\0'; g++)
		if (!is_delim(str[g], d) && (is_delim(str[g + 1], d) || !str[g + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (g = 0, w = 0; w < numwords; w++)
	{
		while (is_delim(str[g], d))
			g++;
		x = 0;
		while (!is_delim(str[g + x], d) && str[g + x])
			x++;
		s[w] = malloc((x + 1) * sizeof(char));
		if (!s[w])
		{
			for (x = 0; x < w; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (c = 0; c < x; c++)
			s[w][c] = str[g++];
		s[w][c] = 0;
	}
	s[w] = NULL;
	return (s);
}

/**
 * **strtow2 - To  splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int g, w, x, c, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (g = 0; str[g] != '\0'; g++)
		if ((str[g] != d && str[g + 1] == d) ||
		    (str[g] != d && !str[g + 1]) || str[g + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (g = 0, w = 0; w < numwords; w++)
	{
		while (str[g] == d && str[g] != d)
			g++;
		x = 0;
		while (str[g + x] != d && str[g + x] && str[g + x] != d)
			x++;
		s[w] = malloc((x + 1) * sizeof(char));
		if (!s[w])
		{
			for (x = 0; x < w; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (c = 0; c < x; c++)
			s[w][c] = str[g++];
		s[w][c] = 0;
	}
	s[w] = NULL;
	return (s);
}
