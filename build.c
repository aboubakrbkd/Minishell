/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:20:17 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/19 17:07:58 by mkimdil          ###   ########.fr       */
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

int build_arr(t_cmd **lst, char **res)
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
