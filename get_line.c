#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t j = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		j = getline(buf, &len_p, stdin);
#else
		j = _getline(info, buf, &len_p);
#endif
		if (j > 0)
		{
			if ((*buf)[j - 1] == '\n')
			{
				(*buf)[j - 1] = '\0';
				j--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = j;
				info->cmd_buf = buf;
			}
		}
	}
	return (j);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, k, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		k = i;
		p = buf + i;

		check_chain(info, buf, &k, i, len);
		while (k < len)
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}

		i = k + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: j
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t j = 0;

	if (*i)
		return (0);
	j = read(info->readfd, buf, READ_BUF_SIZE);
	if (j >= 0)
		*i = j;
	return (j);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: n
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, n = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		n = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, n, n ? n + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (n)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	n += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = n;
	*ptr = p;
	return (n);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
