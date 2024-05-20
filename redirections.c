/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:12:05 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/20 19:04:44 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_out(t_cmd *node, int *index, int flags)
{
	int	j;

	if (node->argv[*index + 1])
	{
		if (node->outfile != 1)
			close(node->outfile);
		if (ft_strchr(node->argv[*index + 1], '$'))
			return (write(2,"minishell: ambiguous redirect\n", 31), 1);
		node->outfile = open(node->argv[*index + 1], flags, 0644);
		if (node->outfile == -1)
			msg_error("open");
		j = *index;
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
		*index -= 1;
	}
	return (0);
}

void	redirect_out_append(t_cmd *node, int *index, int flags)
{
	int	j;

	if (node->argv[*index + 1])
	{
		if (node->outfile != 1)
			close(node->outfile);
		node->outfile = open(node->argv[*index + 1], flags, 0644);
		if (node->outfile == -1)
			msg_error("open");
		j = *index;
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
		*index -= 1;
	}
}

void	error_open(char *str)
{
	perror(str);
	return ;
}

void	redirect_in(t_cmd *node, int *index, int flags)
{
	int	j;

	if (node->argv[*index + 1])
	{
		if (node->infile != 0)
			close(node->infile);
		node->infile = open(node->argv[*index + 1], flags);
		if (node->infile == -1)
			error_open("open");
		j = *index;
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
		*index -= 1;
	}
}

int	check_for_redirection(t_cmd *node)
{
	int	i;

	i = 0;
	while (node->argv[i])
	{
		if (!ft_strcmp(node->argv[i], ">"))
		{
			if (redirect_out(node, &i, O_WRONLY | O_CREAT | O_TRUNC) == 1)
				return (1);
		}
		else if (!ft_strcmp(node->argv[i], ">>"))
			redirect_out_append(node, &i, O_WRONLY | O_CREAT | O_APPEND);
		else if (!ft_strcmp(node->argv[i], "<"))
			redirect_in(node, &i, O_RDONLY);
		i++;
	}
	return (0);
}
