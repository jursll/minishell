/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:36:16 by julrusse          #+#    #+#             */
/*   Updated: 2024/12/22 15:03:19 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*read_and_stash(int fd, char *stash)
{
	int		nbytes;
	char	*buf;

	buf = (char *)gnl_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (NULL);
	nbytes = 1;
	while (nbytes > 0)
	{
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (nbytes == -1)
			return (free(stash), free(buf), NULL);
		buf[nbytes] = '\0';
		if (nbytes == 0)
			break ;
		stash = gnl_strjoin(stash, buf);
		if (!stash)
			return (free(buf), NULL);
		if (gnl_strchr(stash, '\n'))
			break ;
	}
	free(buf);
	return (stash);
}

static char	*line_from_stash(char *prev_stash)
{
	int		i;
	char	*line;

	i = 0;
	while (prev_stash[i] && prev_stash[i] != '\n')
		i++;
	line = gnl_substr(prev_stash, 0, i + 1);
	return (line);
}

static char	*clear_stash(char	*prev_stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	while (prev_stash[i] && prev_stash[i] != '\n')
		i++;
	if (!prev_stash[i])
		return (free(prev_stash), prev_stash = NULL, NULL);
	new_stash = gnl_substr(prev_stash, i + 1, (gnl_strlen(prev_stash) - i - 1));
	return (free(prev_stash), prev_stash = NULL, new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash), stash = NULL, NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = line_from_stash(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = clear_stash(stash);
	return (line);
}
/*
#include <fcntl.h>	// pour open
#include <stdio.h>	// pour printf
#include <string.h>	// pour strdup

int main(void)
{
    int fd = open("test_fd.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
*/
