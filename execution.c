/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:59:50 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/06 16:12:39 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**dynamic_env(char **envp)
{
	int		i;
	t_env	*env;
	char	**envr;

	i = 0;
	env = env_init(envp);
	while (env)
	{
		i++;
		env = env->next;
	}
	envr = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		envr[i] = ft_strjoin(env->name, "=");
		envr[i] = ft_strjoin(envr[i], env->value);
		i++;
	}
	envr[i] = NULL;
	return (envr);
}

char	*check(char *my_argv)
{
	if (my_argv[0] == '/')
	{
		if (access(my_argv, F_OK | X_OK) == 0)
			return (my_argv);
		else
		{
			printf("error in acces /\n");
			exit(1);
		}
	}
	return (0);
}

char	**get_path(char **envp)
{
	int		i;
	char	**s;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			break ;
		i++;
	}
	s = ft_split(envp[i] + 5, ':');
	return (s);
}

char	*command(char *my_argv, char **envp)
{
	char	**path;
	char	*joiner;
	char	*command_path;
	int		i;

	path = get_path(envp);
	i = 0;
	check(my_argv);
	while (path[i])
	{
		if (access(my_argv, F_OK | X_OK) == 0)
			return (my_argv);
		joiner = ft_strjoin(path[i], "/");
		command_path = ft_strjoin(joiner, my_argv);
		free(joiner);
		if (access(command_path, F_OK | X_OK) == 0)
			return (free_all(path), command_path);
		free(command_path);
		i++;
	}
	return (free_all(path), NULL);
}

void	execution(t_cmd *node, char **envp)
{
	int	fd[2];
	int	id;
	int	fd_int;
	int	fd_out;

	fd_int = dup(0);
	fd_out = dup(1);
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
			node->cmd = command(node->argv[0], envp);
			if (execve(node->cmd, node->argv, dynamic_env(envp)) == -1)
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
			node->cmd = command(node->argv[0], envp);
			if (execve(node->cmd, node->argv, dynamic_env(envp)) == -1)
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
//     t_cmd *node;
//     node = (t_cmd *)malloc(sizeof(t_cmd));
//     node->argv = (char **)malloc(sizeof(char *) * 3);
//     node->argv[0] = ft_strdup("cat");
//     node->argv[1] = NULL;
//     node->argv[2] = NULL;
//     node->next = (t_cmd *)malloc(sizeof(t_cmd));
//     node->next->argv = (char **)malloc(sizeof(char *) * 3);
//     node->next->argv[0] = ft_strdup("ls");
//     node->next->argv[1] = NULL;
//     node->next->argv[2] = NULL;
//     node->next->next = NULL;
//     node->next->next = (t_cmd *)malloc(sizeof(t_cmd));
//     node->next->next->argv = (char **)malloc(sizeof(char *) * 3);
//     node->next->next->argv[0] = ft_strdup("wc");
//     node->next->next->argv[1] = NULL;
//     node->next->next->argv[2] = NULL;
//     node->next->next->next = NULL;
//     execution(node, envp);
// }