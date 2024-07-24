/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:16:45 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/25 00:30:40 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_case(char c)
{
	return (is_ascii(c) || is_number(c) || c == '_');
}

void	expand_with_space(t_cmd *lst, t_list *envp, int	*i)
{
	int	j;
	int	k;

	lst->ambiguous = 1;
	envp->splited = ft_split(envp->expanded, ' ');
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

void	expand_without_space(t_cmd *lst, t_list *envp, int *i, int *tr)
{
	lst->argv[*i] = ft_strdup(envp->expanded);
	if (ft_strlen(envp->expanded) == 0 && lst->ambiguous == 0)
	{
		if (*tr != 1 && *tr != 2)
			lst->ambiguous = 1;
		lst->argv[*i] = NULL;
	}
}

void	expand_helper(t_cmd *lst, t_list *envp, int *i, int *tr)
{
	if (ft_strsearch(lst->argv[*i], '"'))
		*tr = 1;
	if (ft_strsearch(lst->argv[*i], '\''))
		*tr = 2;
	if (*tr == 1 || *tr == 0)
	{
		envp->expanded = expand_cmd(lst, envp, *i);
		if (ft_strsearch(envp->expanded, ' ') && *tr == 0)
			expand_with_space(lst, envp, i);
		else
			expand_without_space(lst, envp, i, tr);
	}
}

void	expand(t_cmd *lst, t_list *envp)
{
	int	i;
	int	tr;

	tr = 0;
	while (lst)
	{
		i = 0;
		while (lst->argv[i])
		{
			if (ft_strchr(lst->argv[i], '$') && lst->argv[i + 1]
				&& !ft_strchr(lst->argv[i + 1], '$'))
					envp->tmp = lst->argv[i + 1];
			if (ft_strchr(lst->argv[i], '$'))
				expand_helper(lst, envp, &i, &tr);
			if (envp->tmp && !lst->argv[i])
				lst->argv[i] = ft_strdup(envp->tmp);
			i++;
		}
		lst = lst->next;
	}
}

// void	expand(t_cmd *lst, t_list *envp)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		tr;
// 	int		argv_size;
// 	char	*expanded;
// 	char	**splited;
// 	char	*tmp;

// 	tr = 0;
// 	tmp = NULL;
// 	while (lst)
// 	{
// 		i = 0;
// 		while (lst->argv[i])
// 		{
// 			if (ft_strchr(lst->argv[i], '$') && lst->argv[i + 1]
// 				&& !ft_strchr(lst->argv[i + 1], '$'))
// 				tmp = lst->argv[i + 1];
// 			if (ft_strchr(lst->argv[i], '$'))
// 			{
// 				if (ft_strsearch(lst->argv[i], '"'))
// 					tr = 1;
// 				if (ft_strsearch(lst->argv[i], '\''))
// 					tr = 2;
// 				if (tr == 1 || tr == 0)
// 				{
// 					expanded = expand_cmd(lst, envp, i);
// 					if (ft_strsearch(expanded, ' ') && tr == 0)
// 					{
// 						lst->ambiguous = 1;
// 						splited = ft_split(expanded, ' ');
// 						argv_size = 0;
// 						while (lst->argv[argv_size])
// 							argv_size++;
// 						j = 0;
// 						while (splited[j])
// 							j++;
// 						k = argv_size;
// 						while (k >= i)
// 						{
// 							lst->argv[k + j - 1] = lst->argv[k];
// 							k--;
// 						}
// 						j = 0;
// 						k = i;
// 						while (splited[j])
// 						{
// 							lst->argv[k] = ft_strdup(splited[j]);
// 							k++;
// 							j++;
// 						}
// 					}
// 					else
// 					{
// 						lst->argv[i] = ft_strdup(expanded);
// 						if (ft_strlen(expanded) == 0 && lst->ambiguous == 0)
// 						{
// 							if (tr != 1 && tr != 2)
// 								lst->ambiguous = 1;
// 							lst->argv[i] = NULL;
// 						}
// 					}
// 				}
// 			}
// 			if (tmp && !lst->argv[i])
// 				lst->argv[i] = ft_strdup(tmp);
// 			i++;
// 		}
// 		lst = lst->next;
// 	}
// }
