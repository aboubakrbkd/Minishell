/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:16:45 by mkimdil           #+#    #+#             */
/*   Updated: 2024/08/11 22:10:05 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_with_space(t_cmd *lst, char *expanded, int *i)
{
	if (check_is_ambg(expanded))
		lst->fl1 = 1;
	else
		lst->ambiguous = 1;
	free(lst->argv[*i]);
	lst->argv[*i] = ft_strdup(expanded);
}

void	expand_without_space(t_cmd *lst, int *tr, int *i, char *expanded)
{
	if (lst->argv[*i] && expanded)
	{
		free(lst->argv[*i]);
		lst->argv[*i] = ft_strdup(expanded);
	}
	if (lst->argv[*i] && !expanded)
	{
		if (*tr != 1 && *tr != 2)
			lst->ambiguous = 1;
		free(lst->argv[*i]);
		lst->argv[*i] = NULL;
	}
}

void	check_expanded(t_cmd *lst, int *i, int *tr)
{
	if (!ft_strcmp(lst->argv[0], "export"))
		lst->fl1 = 1;
	if (lst->argv[*i] && ft_strsearch(lst->argv[*i], '"'))
		(1) && (*tr = 1, lst->in_quote = 2, 0);
	if (lst->argv[*i] && ft_strsearch(lst->argv[*i], '\''))
		(1) && (lst->in_quote = 2, *tr = 2, 0);
}

void	expand_helper(t_cmd *lst, t_list *envp, int *i, int *tr)
{
	char	*ex;

	ex = NULL;
	check_expanded(lst, i, tr);
	ex = expand_cmd(lst, envp, *i);
	if (*tr == 1 || *tr == 0)
	{
		if (ex && ((ft_strchr(ex, ' ') || ft_strchr(ex, '\t'))) && *tr == 0)
			(1) && (lst->fl1 = 0, expand_with_space(lst, ex, i), 0);
		else
			(1) && (lst->fl1 = 2, expand_without_space(lst, tr, i, ex), 0);
	}
	if (*tr == 2)
	{
		if (ft_strnstr(lst->argv[*i], "$'"))
			(1) && (free(lst->argv[*i]), lst->argv[*i] = ft_strdup(ex + 1), 0);
		else
			(1) && (free(lst->argv[*i]), lst->argv[*i] = ft_strdup(ex), 0);
	}
	free(ex);
}

void	expand(t_cmd *lst, t_list *envp)
{
	int		i;
	char	*tmp;
	int		tr;

	tr = 0;
	while (lst)
	{
		lst->fl1 = -1;
		i = 0;
		tmp = NULL;
		while (lst->argv[i])
		{
			if (ft_strchr(lst->argv[i], '$'))
				expand_helper(lst, envp, &i, &tr);
			i++;
		}
		remove_null_values(lst->argv, i);
		if (lst->fl1 == 0)
			lst->argv = append(lst->argv, i);
		lst = lst->next;
	}
}
