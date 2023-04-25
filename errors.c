#include "shell.h"

/**
 * _eputs - It prints an input string
 * @str: This is the string to be printed
 *
 * Return: Nothing 0.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - It writes character c into stderr
 * @c: This is the character to be printed
 *
 * Return: success 1.
 * On error, -1 is to be returned, errno is to be set.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
		}
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - It writes character c into the given fd
 * @c: The character to be printed
 * @fd: The filedescriptor to be written to
 *
 * Return: On success 1.
 * On error, -1 is to be returned, errno is set correctly.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putsfd - It will prints an input string
 * @str: this is the string to be printed
 * @fd: tis is the  filedescriptor to written
 *
 * Return: the num of the chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}

	return (i);
}
