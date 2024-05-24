/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:53 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/24 16:00:28 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_arr(t_cmd *lst)
{
	while (lst)
	{
		lst->argv = ft_split(lst->cmd, ' ');
		lst = lst->next;
	}
}

t_cmd	*build_arr(char **res)
{
	int		i;
	t_cmd	*node;
	t_cmd	*final;
	t_cmd	*new_node;

	i = -1;
	final = NULL;
	while (res[++i])
	{
		new_node = malloc(sizeof(t_cmd));
		if (!new_node)
			exit(EXIT_FAILURE);
		new_node->cmd = nops_strdup(res[i]);
		new_node->infile = 0;
		new_node->outfile = 1;
		if (final == NULL)
		{
			final = new_node;
			node = final;
		}
		else
		{
			node->next = new_node;
			node = node->next;
		}
	}
	return (final);
}

