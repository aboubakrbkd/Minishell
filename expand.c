/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:16:45 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/29 03:43:30 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_with_space(t_cmd *lst, char *expanded)
{
	lst->ambiguous = 1;
	lst->argv = join_args(lst->argv, expanded);
}

void	expand_without_space(t_cmd *lst, int *tr, int *i, char *expanded)
{
	free(lst->argv[*i]);
	lst->argv[*i] = ft_strdup(expanded);
	if (ft_strlen(expanded) == 0 && lst->ambiguous == 0)
	{
		if (*tr != 1 && *tr != 2)
			lst->ambiguous = 1;	
		free(lst->argv[*i]);
		lst->argv[*i] = NULL;
	}
}

void	expand_helper(t_cmd *lst, t_list *envp, int *i, int *tr)
{
	char	*expanded;

	*tr = 0;
	if (ft_strsearch(lst->argv[*i], '"'))
		*tr = 1;
	if (ft_strsearch(lst->argv[*i], '\''))
		*tr = 2;
	if (*tr == 1 || *tr == 0)
	{
		expanded = expand_cmd(lst, envp, *i);
		if (expanded == NULL)
			expanded = ft_strdup("");
		if (ft_strsearch(expanded, ' ') && *tr == 0)
			expand_with_space(lst, expanded);
		else
			expand_without_space(lst, tr, i, expanded);
		free(expanded);
	}
	if (*tr == 2)
	{
		expanded = expand_cmd(lst, envp, *i);
		if (expanded == NULL)
			expanded = ft_strdup("");
		free(lst->argv[*i]);
		if (ft_strnstr(lst->argv[*i], "$'"))
			lst->argv[*i] = ft_strdup(expanded + 1);
		else
			lst->argv[*i] = ft_strdup(expanded);
		free(expanded);
	}
}

void	expand(t_cmd *lst, t_list *envp)
{
	int		i;
	char	*tmp;
	int		tr;

	tr = 0;
	while (lst)
	{
		i = 0;
		tmp = NULL;
		while (lst->argv[i])
		{
			if (ft_strchr(lst->argv[i], '$') && lst->argv[i + 1]
				&& !ft_strchr(lst->argv[i + 1], '$'))
				tmp = lst->argv[i + 1];
			if (ft_strchr(lst->argv[i], '$'))
				expand_helper(lst, envp, &i, &tr);
			if (tmp && !lst->argv[i])
				lst->argv[i] = ft_strdup(tmp);
			i++;
		}
		lst = lst->next;	
	}
}
