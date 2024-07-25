/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:16:45 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/25 01:54:38 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_case(char c)
{
	return (is_ascii(c) || is_number(c) || c == '_');
}

void	expand_with_space(t_cmd *lst, t_list *envp, int	*i, char *expanded)
{
	int	j;
	int	k;

	lst->ambiguous = 1;
	envp->splited = ft_split(expanded, ' ');
	envp->argv_size = 0;
	while (lst->argv[envp->argv_size])
		envp->argv_size++;
	j = 0;
	while (envp->splited[j])
		(j)++;
	k = envp->argv_size;
	while (k >= *i)
	{
		lst->argv[k - j - 1] = lst->argv[k];
		k--;
	}
	j = 0;
	k = *i;
	while (envp->splited[j])
	{
		lst->argv[k] = ft_strdup(envp->splited[j]);
		k++;
		j++;
	}
}

void	expand_without_space(t_cmd *lst, t_list *envp, int *i, char *expanded)
{
	lst->argv[*i] = ft_strdup(expanded);
	if (ft_strlen(expanded) == 0 && lst->ambiguous == 0)
	{
		if (envp->tr != 1 && envp->tr != 2)
			lst->ambiguous = 1;
		lst->argv[*i] = NULL;
	}
}

void	expand_helper(t_cmd *lst, t_list *envp, int *i)
{
	char	*expanded;

	if (ft_strsearch(lst->argv[*i], '"'))
		envp->tr = 1;
	if (ft_strsearch(lst->argv[*i], '\''))
		envp->tr = 2;
	if (envp->tr == 1 || envp->tr == 0)
	{
		expanded = expand_cmd(lst, envp, *i);
		if (ft_strsearch(expanded, ' ') && envp->tr == 0)
			expand_with_space(lst, envp, i, expanded);
		else
			expand_without_space(lst, envp, i, expanded);
	}
	if (envp->tr == 2)
	{
		expanded = expand_cmd(lst, envp, *i);
		if (ft_strnstr(lst->argv[*i], "$'"))
			lst->argv[*i] = ft_strdup(expanded + 1);
		else
			lst->argv[*i] = ft_strdup(expanded);
	}
}

void	expand(t_cmd *lst, t_list *envp)
{
	int	i;

	envp->tr = 0;
	while (lst)
	{
		i = 0;
		while (lst->argv[i])
		{
			if (ft_strchr(lst->argv[i], '$') && lst->argv[i + 1]
				&& !ft_strchr(lst->argv[i + 1], '$'))
				envp->tmp = lst->argv[i + 1];
			if (ft_strchr(lst->argv[i], '$'))
				expand_helper(lst, envp, &i);
			if (envp->tmp && !lst->argv[i])
				lst->argv[i] = ft_strdup(envp->tmp);
			i++;
		}
		lst = lst->next;
	}
}
