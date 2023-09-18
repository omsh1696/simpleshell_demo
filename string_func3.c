#include "shell.h"
/**
 * _strncat - function that concatenates two strings
 *
 * @dest: input string
 * @src: input string
 * @n: most number of bytes from @src
 *
 * Return: @dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;

	a = 0;
	while (dest[a])
		a++;
	for (b = 0; b < n && src[b] != '\0'; b++)
		dest[a + b] = src[b];
	dest[a + b] = '\0';
	return (dest);
}
/**
 * _strncpy -  function that copies a string
 *
 * @dest: input string
 * @src: input string
 * @n: bytes
 *
 * Return: @dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
/**
 * _strchr - locates character in astring
 * @s: input
 * @c: input
 * Return: Always 0 (Success)
 */
char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; s[i] >= '\0'; i++)
	{
		if (s[i] == c)
			return (&s[i]);
	}
	return (0);
}
