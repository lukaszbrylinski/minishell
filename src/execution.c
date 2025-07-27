#include "minishell.h"

void	handle_redirections(t_rdir *rdir)
{
	int	fd;

	while (rdir)
	{
		fd = -1;
		if (rdir->type == IN)
			fd = open(rdir->target, O_RDONLY);
		else if (rdir->type == OUT)
			fd = open(rdir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (rdir->type == AEND)
			fd = open(rdir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (rdir->type == HDOC)
			fd = open(rdir->target, O_RDONLY);
		if (fd >= 0)
		{
			if (rdir->type == IN || rdir->type == HDOC)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		rdir = rdir->next;
	}
}

int exec_command(t_command *cmd)
{
	char    **argv;
    int     pid;
    int     status;

    argv = build_argv(cmd);
	if (!argv)
		return 1;
	pid = fork();
	if (pid == 0)
	{
		if (cmd->rdir_list)
			handle_redirections(cmd->rdir_list->first);
		execvp(argv[0], argv);
		perror("execvp");
		free_argv(argv);
		free_command(cmd); // zwalniamy pełną strukturę
		exit(1);
	}
	free_argv(argv);
	waitpid(pid, &status, 0);
	return WEXITSTATUS(status);
}

// pipe_helpers.c

void	child_pipe_left(t_ast *left, int *pipefd)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exit(exec_ast(left));
}

void	child_pipe_right(t_ast *right, int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	exit(exec_ast(right));
}

int	exec_pipe(t_ast *left, t_ast *right)
{
	int	pipefd[2];
	int	pid1;
	int	pid2;
	int	status;

	if (pipe(pipefd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == 0)
		child_pipe_left(left, pipefd);
	pid2 = fork();
	if (pid2 == 0)
		child_pipe_right(right, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}

int	exec_ast(t_ast *node)
{
	if (!node)
		return (1);
	if (node->type == CMND_NODE)
		return (exec_command(node->cmnd));
	if (node->type == PIPE_NODE)
		return (exec_pipe(node->pipe.left, node->pipe.right));
	return (1);
}

char **alloc_argv(int total)
{
	char **argv = malloc(sizeof(char *) * (total + 1));
	if (!argv)
		return NULL;
	argv[0] = NULL; // ustawiamy tylko NULL, komenda zostanie przypisana później
	argv[total] = NULL;
	return argv;
}

int	count_args(char **args)
{
	int count = 0;

	while (args && args[count])
		count++;
	return (count);
}
void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

char **build_argv(t_command *cmd)
{
    char    **argv;
    char    **split_args;
    int     base_argv;
    int     i;

	if (!cmd)
		return NULL;
    argv = NULL;
	split_args = NULL;
	base_argc = 0;
	if (cmd->args && cmd->args[0])
	{
		split_args = ft_split(cmd->args[0], ' ');
		if (!split_args)
			return NULL;
		base_argc = count_args(split_args);
	}

	argv = malloc(sizeof(char *) * (base_argc + 2));
	if (!argv)
	{
		free_argv(split_args);
		return NULL;
	}

	argv[0] = ft_strdup(cmd->cmnd);
	if (!argv[0])
	{
		free_argv(argv);
		free_argv(split_args);
		return NULL;
	}

	for (int i = 0; split_args && split_args[i]; i++)
	{
		argv[i + 1] = ft_strdup(split_args[i]);
		if (!argv[i + 1])
		{
			free_argv(argv);
			free_argv(split_args);
			return NULL;
		}
	}
	argv[base_argc + 1] = NULL;
	free_argv(split_args);
	return argv;
}
