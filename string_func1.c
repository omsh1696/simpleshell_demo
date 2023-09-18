#include "shell.h"
/**
 * _strlen - the length of string
 *
 * @s: string input
 *
 * Return: i the lenght of string
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; *s != '\0'; s++)
		++i;

	return (i);
}
/**
 * _strcmp - function thar compare two string
 * @s1: input string
 * @s2: input string
 * Return: 0 if s1 == s2 , -1 if s1 < s2, 1 if s1 > s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * _strcat - concatenate two strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return: pointer to concatenated string
 */

char *_strcat(char *s1, char *s2)
{
	int i = 0, j = 0;

	while (s1[i] != '\0')
	{
		i++;
	}

	while (s2[j] != '\0')
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}
/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: substring to find
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
