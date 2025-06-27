/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:04:16 by dszafran          #+#    #+#             */
/*   Updated: 2025/02/25 18:42:53 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	read_to_buffer(char **saved, int fd)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 1)
		return (free(buffer), bytes_read);
	buffer[bytes_read] = 0;
	temp = ft_strjoin(*saved, buffer);
	free(*saved);
	*saved = temp;
	free(buffer);
	if (!(*saved))
		return (-1);
	return (bytes_read);
}

static char	*extract_line(char **saved)
{
	size_t	i;
	char	*temp;
	char	*line;

	i = 0;
	while ((*saved)[i] && (*saved)[i] != '\n')
		i++;
	if ((*saved)[i] == '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	ft_strlcpy(line, *saved, i + 1);
	temp = ft_strdup((*saved) + i);
	free(*saved);
	*saved = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved[1024];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(saved[fd], '\n') && bytes_read > 0)
		bytes_read = read_to_buffer(&(saved[fd]), fd);
	if (bytes_read == -1 || (bytes_read == 0
			&& (!(saved[fd]) || !(*saved[fd]))))
	{
		if (saved[fd])
			free(saved[fd]);
		return (NULL);
	}
	line = extract_line(&(saved[fd]));
	return (line);
}
