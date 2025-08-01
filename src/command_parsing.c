// add header

#include "minishell.h"

char    **append_array(char **array, char *str)
{
    char **new_array;
    int  i;

    if (!str)
        return (array);
    if (!array)
    {
        array = malloc(sizeof(char *) * 2);
        array[0] = str;
        array[1] = NULL;
        return (array);
    }
    i = 0;
    while (array[i] != NULL)
        i++;
    new_array = malloc(sizeof(char *) * (i + 2));
    i = -1;
    while (array[++i]) 
        new_array[i] = array[i];
    new_array[i] = str;
    new_array[i + 1] = NULL;
    return (new_array);
}

char	**get_args(t_token_list *list)
{
	char	**args;
	t_token	*current;

	if (!list->first->next)
		return (NULL);
	args = NULL;
	current = list->first->next;
	while (current && current->type != RDIR)
	{
		args = append_array(args, ft_strdup(current->token));
		current = current->next;
	}
	return (args);
}

t_command	*parse_command(t_token_list *list)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->cmnd = ft_strdup(list->first->token);
	if (!command->cmnd)
		return (free(command), NULL);
	command->rdir_list = get_rdirs(list);
	command->args = get_args(list);
	return (command);
}

void	print_command(t_command *command)
{
	int		i;
	t_rdir	*current;

	if (!command)
		return ;
	printf("Printing command:\n");
	printf("cmnd:\n");
	if (command->cmnd)
		printf("%s\n", command->cmnd);
	printf("\nargs:\n");
	if (command->args)
	{	
		i = -1;
		if (command->args)
			while (command->args[++i])
				printf("%s, ", command->args[i]);
	}
	printf("\nrdirs:\n");
	if (command->rdir_list)
	{
		current = command->rdir_list->first;
		while (current)
		{
			print_rdir(current);
			current = current->next;
		}
	}
	printf("\n\n");
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmnd)
		free(cmd->cmnd);
	if (cmd->args)
		ft_free_split(cmd->args);
	if (cmd->rdir_list)
		free_rdirs(cmd->rdir_list);
	free(cmd);
}
