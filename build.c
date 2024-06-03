/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:53 by aboukdid          #+#    #+#             */
/*   Updated: 2024/06/03 16:47:34 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_arr_help(t_cmd **lst, char *res)
{
	(*lst)->cmd = nops_strdup(res);
	(*lst)->argv = ft_split((*lst)->cmd, ' ');
	(*lst)->infile = 0;
	(*lst)->outfile = 1;
	(*lst)->next = NULL;
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
		build_arr_help(&new_node, res[i]);
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
