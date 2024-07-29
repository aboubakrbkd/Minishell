/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:50:50 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/29 20:05:20 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exp(t_expand *exp)
{
	t_expand	*curr;

	curr = exp;
	free(curr->current);
	free(curr->var_name);
	free(curr->value);
	free(curr);
}

void	free_list(t_list *list)
{
	t_env	*current;
	t_env	*next;

	current = list->envs;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	free(list);
}

void	free_cmd_lst(t_cmd **lst)
{
	t_cmd	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->cmd);
		free_all((*lst)->argv);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}

int	ft_strsearch(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (i < ft_strlen(s) + 1)
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}
