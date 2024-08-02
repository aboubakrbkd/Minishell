/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:12:05 by aboukdid          #+#    #+#             */
/*   Updated: 2024/08/02 18:26:25 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_out_append(t_cmd *node, int *index, int flags)
{
	int		j;
	char	*str;

	if (checking_ambigious(node) == 1)
		return (1);
	if (node->argv[*index + 1])
	{
		if (node->outfile != 1)
			close(node->outfile);
		node->outfile = open(node->argv[*index + 1], flags, 0644);
		if (node->outfile == -1)
		{
			str = ft_strjoin("minishell: ", node->argv[*index + 1]);
			msg_error(str);
			free(str);
			ex_st(1, 1);
			return (1);
		}
		j = *index;
		new_array(node, index, j);
	}
	return (0);
}

int	redirect_in(t_cmd *node, int *index, int flags)
{
	int		j;
	char	*str;

	if (checking_ambigious(node) == 1)
		return (1);
	if (node->argv[*index + 1])
	{
		if (node->inf != 0)
			close(node->inf);
		node->inf = open(node->argv[*index + 1], flags);
		if (node->inf == -1)
		{
			str = ft_strjoin("minishell: ", node->argv[*index + 1]);
			msg_error(str);
			ex_st(1, 1);
			free(str);
			return (1);
		}
		j = *index;
		new_array(node, index, j);
	}
	return (0);
}

int	redirect_out(t_cmd *node, int *index, int flags)
{
	int		j;
	char	*str;

	if (checking_ambigious(node) == 1)
		return (1);
	if (node->argv[*index + 1])
	{
		if (node->outfile != 1)
			close(node->outfile);
		node->outfile = open(node->argv[*index + 1], flags, 0644);
		if (node->outfile == -1)
		{
			str = ft_strjoin("minishell: ", node->argv[*index + 1]);
			msg_error(str);
			free(str);
			ex_st(1, 1);
			return (1);
		}
		j = *index;
		new_array(node, index, j);
	}
	return (0);
}

int	check_for_redirection(t_cmd *node)
{
	int	i;
	int	fail;

	i = 0;
	fail = 0;
	while (node->argv[i])
	{
		if (!ft_strcmp(node->argv[i], ">"))
			fail = redirect_out(node, &i, O_RDWR | O_CREAT | O_TRUNC);
		else if (!ft_strcmp(node->argv[i], ">>"))
			fail = redirect_out_append(node, &i, O_WRONLY | O_CREAT | O_APPEND);
		else if (!ft_strcmp(node->argv[i], "<"))
			fail = redirect_in(node, &i, O_RDONLY);
		else if (!ft_strcmp(node->argv[i], "<<"))
			new_array(node, &i, i);
		if (fail == 1 || fail == 2)
			return (fail);
		i++;
	}
	return (0);
}
