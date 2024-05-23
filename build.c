/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:53 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/23 22:45:08 by mkimdil          ###   ########.fr       */
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

int	build_arr(t_cmd **lst, char **res)
{
	int		i;
	t_cmd	*new_node;
	t_cmd	*curr;

	new_node = NULL;
	curr = NULL;
	i = 0;
	while (res[i])
	{
		new_node = new_list(nops_strdup(res[i]));
		if (!new_node->cmd)
			return (free(new_node), 1);
		if (!*lst)
			*lst = new_node;
		else
			curr->next = new_node;
		curr = new_node;
		i++;
	}
	return (0);
}
