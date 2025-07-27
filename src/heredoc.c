
#include "minishell.h"

char	*gen_tmpfile_name(void)
{
	static int	counter;
	char		*name;

	counter = 0;
	name = malloc(32);
	if (!name)
		return (NULL);
	printf(name, "/tmp/heredoc_%d.tmp", counter);
	counter++;
	return (name);
}

int	read_heredoc(const char *delimiter, char **filename)
{
	char	*line;
	int		fd;

	*filename = gen_tmpfile_name();
	if (!*filename)
		return (-1);
	fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}
