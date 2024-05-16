/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:59:50 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/16 13:27:59 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_global	g_global;

char	**env_to_char_array(t_env *head)
{
	int		i;
	char	**envp;
	t_env	*current;

	i = 0;
	current = head;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	envp = malloc((i + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	current = head;
	i = 0;
	while (current)
	{
		if (!current->value)
			envp[i] = ft_strjoin_with_sep(current->name, "", '=');
		else
			envp[i] = ft_strjoin_with_sep(current->name, current->value, '=');
		i++;
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	execution(t_cmd *node, char **envp)
{
	int		fd[2];
	int		id;
	int		fd_int;
	int		fd_out;
	char	**envr;

	fd_int = dup(0);
	fd_out = dup(1);
	envr = env_to_char_array(g_global.envs);
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
			node->cmd = command(node->argv[0], envr);
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
		id = fork();
		if (id == -1)
		{
			perror("fork");
			exit(1);
		}
		if (id == 0)
		{
			node->cmd = command(node->argv[0], envr);
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

// int main(int argc, char **argv,  char **envp)
// {
// 	g_global.envs = env_init(envp);
// 	t_cmd *node;
// 	node = (t_cmd *)malloc(sizeof(t_cmd));
// 	node->argv = (char **)malloc(sizeof(char *) * 3);
// 	node->argv[0] = ft_strdup("cat");
// 	node->argv[1] = NULL;
// 	node->argv[2] = NULL;
// 	node->next = (t_cmd *)malloc(sizeof(t_cmd));
// 	node->next->argv = (char **)malloc(sizeof(char *) * 3);
// 	node->next->argv[0] = ft_strdup("ls");
// 	node->next->argv[1] = NULL;
// 	node->next->argv[2] = NULL;
// 	node->next->next = NULL;
// 	node->next->next = (t_cmd *)malloc(sizeof(t_cmd));
// 	node->next->next->argv = (char **)malloc(sizeof(char *) * 3);
// 	node->next->next->argv[0] = ft_strdup("wc");
// 	node->next->next->argv[1] = NULL;
// 	node->next->next->argv[2] = NULL;
// 	node->next->next->next = NULL;
// 	execution(node, envp);
// }
