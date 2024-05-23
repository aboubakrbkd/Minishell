/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:59:50 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/19 17:56:28 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_multiple_commands(t_cmd *node, t_list *list, char **envr)
{
	int	fd[2];
	int	id;

	check_for_redirection(node);
	safe_pipe(fd);
	id = safe_fork();
	if (id == 0)
	{
		handle_duplications(node, fd);
		if (is_builtin(node, list))
			exit(0);
		node->cmd = command(node->argv[0], envr);
		if (execve(node->cmd, node->argv, envr) == -1)
			msg_error("execve");
	}
	if (node->infile != 0)
		close(node->infile);
	if (node->outfile != 1)
		close(node->outfile);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		msg_error("dup2 in fd[0]");
	close(fd[0]);
}

void	handle_last_command(t_cmd *node, char **envr, int id)
{
	if (is_builtin(node, NULL))
	{
		handle_builtin_command(node, 0, 1);
		return ;
	}
	id = fork();
	if (id == 0)
	{
		handle_duplications(node, NULL);
		node->cmd = command(node->argv[0], envr);
		if (execve(node->cmd, node->argv, envr) == -1)
			msg_error("execve");
		if (node->infile != 0)
			close(node->infile);
		if (node->outfile != 1)
			close(node->outfile);
	}
}

void	parent_process(int fd_int, int fd_out)
{
	dup2(fd_int, 0);
	close(fd_int);
	dup2(fd_out, 1);
	close(fd_out);
	while (wait(NULL) != -1)
		;
}

void	last_command(t_cmd *node, char **envr)
{
	handle_duplications(node, NULL);
	node->cmd = command(node->argv[0], envr);
	if (execve(node->cmd, node->argv, envr) == -1)
		msg_error("execve");
}

int	execution(t_cmd *node, t_list *list)
{
	int		id;
	int		fd_int;
	int		fd_out;
	char	**envr;

	fd_int = dup(0);
	fd_out = dup(1);
	envr = env_to_char_array(list->envs);
	while (node->next)
	{
		handle_multiple_commands(node, list, envr);
		node = node->next;
	}
	if (node)
	{
		check_for_redirection(node);
		if (is_builtin(node, list))
			return (handle_builtin_command(node, fd_int, fd_out), 0);
		id = safe_fork();
		if (id == 0)
			last_command(node, envr);
		close_files(node);
	}
	parent_process(fd_int, fd_out);
	return (0);
}
