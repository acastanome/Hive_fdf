/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:02:58 by acastano          #+#    #+#             */
/*   Updated: 2022/04/14 16:43:55 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#define BUFF_SIZE 32
#define FD_MAX 8192

/*
**Looks for a line (chars ending with \n) in saved_text.
**First parameter is the address of a pointer to a character where we
** will looks for a line.
**Second parameter is the address of a pointer to a pointer to a character
** that will be used to save the line read from the saved_text.
**If a \n is found, mallocs line to be contents of saved_text before \n,
** and saved_text after \n.
**Return values: 0 if no \n, 1 if \n and -1 upon error(when malloc)
*/
static int	ft_is_newline(char **saved_text, char ***line)
{
	char	*location;
	char	*temp;

	temp = NULL;
	location = ft_strchr(*saved_text, '\n');
	if (location)
	{
		**line = ft_strsub(*saved_text, 0, (location - *saved_text));
		if (!(**line))
			return (-1);
		if (*(location + 1) == '\0')
		{
			free(*saved_text);
			*saved_text = NULL;
		}
		else
		{
			temp = ft_strdup(location + 1);
			free(*saved_text);
			*saved_text = temp;
		}
		return (1);
	}
	return (0);
}

/*
**If no text saved in saved_text, reads and saves it.
**Return values: 0 if doesn't read, 1 if it does and -1 if error.
*/
static int	ft_get_text(char **saved_text, const int fd)
{
	char	*buf;
	ssize_t	chars_read;
	char	*temp;

	buf = ft_strnew(BUFF_SIZE + 1);
	if (!buf)
		return (-1);
	chars_read = read(fd, buf, BUFF_SIZE);
	if (chars_read > 0)
	{
		if (*saved_text == NULL)
			*saved_text = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(*saved_text, buf);
			free(*saved_text);
			*saved_text = temp;
		}
		free(buf);
		if (!(*saved_text))
			return (-1);
	}
	if (chars_read <= 0)
		free(buf);
	return (chars_read);
}

/*
**If no line previously found, looks for a line (characters except '\0')
** in saved_text, mallocs line from it, and free's saved_text.
**If an error occurs, free's saved_text.
**Return values: 0 if no line, 1 if line and -1 upon error.
*/
static int	ft_is_line(char **saved_text, char ***line, int found_line)
{
	if (found_line == 0)
	{
		if ((*saved_text != NULL) && (ft_strlen(*saved_text) != 0))
		{
			**line = ft_strdup(*saved_text);
			if (!(**line))
				found_line = -1;
			else
				found_line = 1;
			ft_strdel(&(*saved_text));
		}
	}
	if (found_line == -1)
		ft_strdel(&(*saved_text));
	return (found_line);
}

/*
**Returns a line (chars ending with \n or EOF) read from a fd, without the \n.
**First parameter is the file descriptor that will be used to read.
**Second parameter is the address of a pointer to a character
** that will be used to save the line read from the file descriptor.
**Return values: 1, 0 or -1 depending on whether a line has been read,
** when the reading has been completed, or if an error has happened.
*/
int	get_next_line(const int fd, char **line)
{
	static char	*fd_tracker[FD_MAX + 1];
	ssize_t		chars_read;
	int			found_line;

	if (fd < 0 || line == NULL || fd >= FD_MAX || BUFF_SIZE <= 0)
		return (-1);
	*line = NULL;
	chars_read = 0;
	found_line = 0;
	while (*line == NULL)
	{
		if (fd_tracker[fd] != NULL)
		{
			found_line = ft_is_newline(&fd_tracker[fd], &line);
			if ((found_line == 1) || (found_line < 0))
				break ;
		}
		chars_read = ft_get_text(&fd_tracker[fd], fd);
		if (chars_read <= 0)
			break ;
	}
	if (chars_read < 0)
		found_line = -1;
	found_line = ft_is_line(&fd_tracker[fd], &line, found_line);
	return (found_line);
}
