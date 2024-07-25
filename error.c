/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:50:50 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/25 02:43:03 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handling_shlvl(t_list *list)
{
	char	*shl_lvl;
	char	*lvl;

	shl_lvl = my_getenv("SHLVL", list);
	if (!shl_lvl)
		update_env("SHLVL", "1", list);
	else if (ft_atoi(shl_lvl) > 999)
	{
		printf("Minishell: warning: shell level ");
		printf("(%d) too high, resetting to 1\n", ft_atoi(shl_lvl));
		update_env("SHLVL", "1", list);
	}
	else if (ft_atoi(shl_lvl) < 0)
		update_env("SHLVL", "0", list);
	else if (ft_atoi(shl_lvl) == 999)
		update_env("SHLVL", "", list);
	else
	{
		lvl = ft_itoa(ft_atoi(shl_lvl) + 1);
		if (!lvl)
			exit(EXIT_FAILURE);
		add_the_value("SHLVL", lvl, list);
		free(lvl);
	}
}

void	free_cmd_lst(t_cmd *lst)
{
	t_cmd	*current;
	t_cmd	*next;

	current = lst;
	while (current)
	{
		next = current->next;
		free(current->cmd);
		free_all(current->argv);
		free(current);
		current = next;
	}
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
