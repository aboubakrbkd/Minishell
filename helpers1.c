/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:55:17 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/19 17:56:22 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_duplications(t_cmd *node, int *fd)
{
	if (node->infile != 0)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			msg_error("dup2 infile");
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			msg_error("dup2 outfile");
		close(node->outfile);
	}
	else if (fd != NULL)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			msg_error("dup2 fd[1]");
		close(fd[1]);
	}
}

int	is_builtin(t_cmd *cmd, t_list *list)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (echo(cmd->argv, cmd->outfile), 1);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (cd(cmd->argv, list), 1);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (pwd(cmd->argv, list, cmd->outfile), 1);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (export(cmd->argv, list, cmd->outfile), 1);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (unset(cmd->argv, &list->envs), 1);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (env(cmd->argv, list, cmd->outfile), 1);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (exit_function(cmd->argv), 1);
	return (0);
}

void	env_to_char_array_helper(t_env *current, char **envp)
{
	int	i;

	i = 0;
	while (current)
	{
		if (!current->value)
			envp[i] = ft_strjoin_with_sep(current->name, "", '=');
		else
			envp[i] = ft_strjoin_with_sep(current->name, current->value, '=');
		if (!envp[i])
		{
			free_all(envp);
			return ;
		}
		i++;
		current = current->next;
	}
}

char	**env_to_char_array(t_env *head)
{
	int		i;
	t_env	*current;
	char	**envp;

	i = 0;
	current = head;
	i = env_size(head);
	if (i == 0)
		return (NULL);
	envp = malloc((i + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	current = head;
	env_to_char_array_helper(current, envp);
	envp[i] = NULL;
	return (envp);
}
