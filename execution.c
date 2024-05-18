/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:59:50 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/18 20:41:18 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

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


void check_for_redirection(t_cmd *node)
{
    int i;
    int j;

    i = 0;
    while (node->argv[i])
    {
        if (!strcmp(node->argv[i], ">"))
        {
            if (node->argv[i + 1])
            {
                if (node->outfile != 1)
                    close(node->outfile);
                node->outfile = open(node->argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (node->outfile == -1)
                {
                    perror("open");
                    exit(1);
                }
                j = i;
                while (node->argv[j])
                {
                    if (!node->argv[j + 2])
					{
						node->argv[j] = NULL;
						break ;
					}
                    else
                        node->argv[j] = node->argv[j + 2];
                    j++;
                }
                i--;
            }
        }
        else if (!strcmp(node->argv[i], ">>"))
        {
            if (node->argv[i + 1])
            {
                if (node->outfile != 1)
                    close(node->outfile);
                node->outfile = open(node->argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (node->outfile == -1)
                {
                    perror("open");
                    exit(1);
                }
                j = i;
                while (node->argv[j])
                {
                    if (!node->argv[j + 2])
					{
						node->argv[j] = NULL;
						break ;
					}
                    else
                        node->argv[j] = node->argv[j + 2];
                    j++;
                }
                i--;
            }
        }
        else if (!strcmp(node->argv[i], "<"))
        {
            if (node->argv[i + 1])
            {
                node->infile = open(node->argv[i + 1], O_RDONLY);
                if (node->infile == -1)
                {
                    perror("open");
                    exit(1);
                }
                j = i;
                while (node->argv[j])
                {
                    if (!node->argv[j + 2])
					{
						node->argv[j] = NULL;
						break ;
					}
                    else
                        node->argv[j] = node->argv[j + 2];
                    j++;
                }
                i--;
            }
        }
        i++;
    }
}

void	msg_error(char *str)
{
	perror(str);
	exit(1);
}

void	execution(t_cmd *node, t_list *list)
{
	int		fd[2];
	int		id;
	int		fd_int = dup(0);
	int		fd_out = dup(1);
	char	**envr = env_to_char_array(list->envs);

	while (node->next)
	{
		check_for_redirection(node);
		if (pipe(fd) == -1)
			msg_error("pipe");
		id = fork();
		if (id == -1)
			msg_error("fork");
		if (id == 0)
		{
			if (node->infile != 0)
			{
				if (dup2(node->infile, 0) == -1)
					msg_error("dup2 in infile");
				close(node->infile);
			}
			if (node->outfile != 1)
			{
				if (dup2(node->outfile, 1) == -1)
					msg_error("dup2 in outfile");
				close(node->outfile);
			}
			else
			{
				close(fd[0]);
				if (dup2(fd[1], 1) == -1)
					msg_error("dup2 in fd[1]");
				close(fd[1]);
			}
			if (is_builtin(node, list))
				exit(0);
			node->cmd = command(node->argv[0], envr);
			if (!node->cmd)
			{
				perror("command");
				exit(127);
			}
			if (execve(node->cmd, node->argv, envr) == -1)
				msg_error("execve");
		}
		if (node->infile != 0)
			close(node->infile);
		if (node->outfile != 1)
			close(node->outfile);
		close(fd[1]);
		if (dup2(fd[0], 0) == -1)
			msg_error("dup2 in fd[0]");
		close(fd[0]);
		node = node->next;
	}
	if (node)
	{
		check_for_redirection(node);
		if (is_builtin(node, list))
		{
			dup2(fd_int, 0);
			close(fd_int);
			dup2(fd_out, 1);
			close(fd_out);
			return ;
		}
		id = fork();
		if (id == -1)
			msg_error("fork");
		if (id == 0)
		{
			if (node->infile != 0)
			{
				if (dup2(node->infile, 0) == -1)
					msg_error("dup2 in infile2");
				close(node->infile);
			}
			if (node->outfile != 1)
			{
				if (dup2(node->outfile, 1) == -1)
					msg_error("dup2 in outfile2");
				close(node->outfile);
			}
			if (is_builtin(node, list))
				return ;
			node->cmd = command(node->argv[0], envr);
			if (!node->cmd)
			{
				perror("command");
				exit(127);
			}
			if (execve(node->cmd, node->argv, envr) == -1)
				msg_error("execve");
		}
		if (node->infile != 0)
			close(node->infile);
		if (node->outfile != 1)
			close(node->outfile);
	}
	dup2(fd_int, 0);
	close(fd_int);
	dup2(fd_out, 1);
	close(fd_out);
	while (wait(NULL) != -1)
		;
}
