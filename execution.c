/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:59:50 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/16 20:27:30 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	envp = malloc((i + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	current = head;
	env_to_char_array_helper(current, envp);
	envp[i] = NULL;
	return (envp);
}

int	is_builtin(t_cmd *cmd, t_list *list)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (echo(cmd->argv), 1);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (cd(cmd->argv, list), 1);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (pwd(cmd->argv, list), 1);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (export(cmd->argv, list), 1);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (unset(cmd->argv, &list->envs), 1);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (env(cmd->argv, list), 1);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (exit_function(cmd->argv), 1);
	return (0);
}


void	execution(t_cmd *node, t_list *list)
{
	int		fd[2];
	int		id;
	int		fd_int;
	int		fd_out;
	char	**envr;

	fd_int = dup(0);
	fd_out = dup(1);
	envr = env_to_char_array(list->envs);
	while (node->next)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		id = fork();
		if (id == -1)
		{
			perror("fork");
			exit(1);
		}
		if (id == 0)
		{
			close(fd[0]);
			if (dup2(fd[1], 1) == -1)
			{
				perror("dup2");
				exit(1);
			}
			close(fd[1]);
			if (is_builtin(node, list))
				exit(0);
			node->cmd = command(node->argv[0], envr);
			if (!node->cmd)
			{
				perror("command");
				exit(127);
			}
			if (execve(node->cmd, node->argv, envr) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		node = node->next;
	}
	if (node)
	{
		if (is_builtin(node, list))
			return ;
		id = fork();
		if (id == -1)
		{
			perror("fork");
			exit(1);
		}
		if (id == 0)
		{
			node->cmd = command(node->argv[0], envr);
			if (!node->cmd)
			{
				perror("command");
				exit(127);
			}
			if (execve(node->cmd, node->argv, envr) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
	}
	close(fd[0]);
	close(fd[1]);
	dup2(fd_int, 0);
	close(fd_int);
	dup2(fd_out, 1);
	close(fd_out);
	while (wait(NULL) != -1)
		;
}
