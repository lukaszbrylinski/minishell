#include "minishell.h"

// void	handle_redirections(t_rdir *rdir)
// {
// 	int	fd;

// 	while (rdir)
// 	{
// 		fd = -1;
// 		if (rdir->type == IN)
// 			fd = open(rdir->target, O_RDONLY);
// 		else if (rdir->type == OUT)
// 			fd = open(rdir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		else if (rdir->type == AEND)
// 			fd = open(rdir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		else if (rdir->type == HDOC)
// 			fd = open(rdir->target, O_RDONLY);
// 		if (fd >= 0)
// 		{
// 			if (rdir->type == IN || rdir->type == HDOC)
// 				dup2(fd, STDIN_FILENO);
// 			else
// 				dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		rdir = rdir->next;
// 	}
// }

// int exec_command(t_command *cmd)
// {
// 	char **argv = build_argv(cmd);
// 	if (!argv)
// 		return 1;

// 	int pid = fork();
// 	if (pid == 0)
// 	{
// 		if (cmd->rdir_list)
// 			handle_redirections(cmd->rdir_list->first);
// 		execvp(argv[0], argv);
// 		perror("execvp");
// 		free_argv(argv);
// 		free_command(cmd); // zwalniamy pełną strukturę
// 		exit(1);
// 	}

// 	free_argv(argv);
// 	int status;
// 	waitpid(pid, &status, 0);
// 	return WEXITSTATUS(status);
// }

// pipe_helpers.c

// void	child_pipe_left(t_ast *left, int *pipefd)
// {
// 	close(pipefd[0]);
// 	dup2(pipefd[1], STDOUT_FILENO);
// 	close(pipefd[1]);
// 	exit(exec_ast(left));
// }

// void	child_pipe_right(t_ast *right, int *pipefd)
// {
// 	close(pipefd[1]);
// 	dup2(pipefd[0], STDIN_FILENO);
// 	close(pipefd[0]);
// 	exit(exec_ast(right));
// }

// int	exec_pipe(t_ast *left, t_ast *right)
// {
// 	int	pipefd[2];
// 	int	pid1;
// 	int	pid2;
// 	int	status;

// 	if (pipe(pipefd) == -1)
// 		return (1);
// 	pid1 = fork();
// 	if (pid1 == 0)
// 		child_pipe_left(left, pipefd);
// 	pid2 = fork();
// 	if (pid2 == 0)
// 		child_pipe_right(right, pipefd);
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, &status, 0);
// 	return (WEXITSTATUS(status));
// }

// int	exec_ast(t_ast *node)
// {
// 	if (!node)
// 		return (1);
// 	if (node->type == CMND_NODE)
// 		return (exec_command(node->cmnd));
// 	if (node->type == PIPE_NODE)
// 		return (exec_pipe(node->pipe.left, node->pipe.right));
// 	return (1);
// }

void free_ast(t_ast *node)
{
	if (!node)
		return;

	if (node->type == CMND_NODE)
		free_command(node->cmnd);
	else if (node->type == PIPE_NODE)
	{
		free_ast(node->pipe.left);
		free_ast(node->pipe.right);
	}

	free(node);
}
