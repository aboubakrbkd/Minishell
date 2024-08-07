/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:16:45 by mkimdil           #+#    #+#             */
/*   Updated: 2024/08/07 04:28:31 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_with_space(t_cmd *lst, char *expanded, int *i)
{
	lst->ambiguous = 1;
	lst->argv = append(lst->argv, expanded, *i);
}

void	expand_without_space(t_cmd *lst, int *tr, int *i, char *expanded)
{
	if (lst->argv[*i] && expanded)
	{
		free(lst->argv[*i]);
		lst->argv[*i] = ft_strdup(expanded);
	}
	else if (!expanded)
	{
		if (*tr != 1 && *tr != 2)
			lst->ambiguous = 1;
		free(lst->argv[*i]);
		lst->argv[*i] = NULL;
	}
}

void	check_expanded(t_cmd *lst, int *i, int *tr)
{
	if (lst->argv[*i] && ft_strsearch(lst->argv[*i], '"'))
		(1) && (*tr = 1, lst->in_quote = 2, 0);
	if (lst->argv[*i] && ft_strsearch(lst->argv[*i], '\''))
		(1) && (lst->in_quote = 2, *tr = 2, 0);
}

void expand_helper(t_cmd *lst, t_list *envp, int *i, int *tr)
{
    char *ex = NULL;

    ex = expand_cmd(lst, envp, *i);
	printf("%s\n", ex);
    if (*tr == 1 || *tr == 0)
    {
        if (ex && ((ft_strchr(ex, ' ') || ft_strchr(ex, '\t'))) && *tr == 0)
            expand_with_space(lst, ex, i);
        else
            expand_without_space(lst, tr, i, ex);
    }
    if (*tr == 2)
    {
        if (ft_strnstr(lst->argv[*i], "$'"))
        {
            free(lst->argv[*i]);
            lst->argv[*i] = ft_strdup(ex + 1);
        }
        else
        {
            free(lst->argv[*i]);
            lst->argv[*i] = ft_strdup(ex);
        }
    }
    free(ex);
}

void	remove_null_values(char **argv, int size)
{
	int	index;
	int	jndex;

		index = 0;
		jndex = 0;
	while (jndex < size)
	{
		if (argv[jndex] != NULL)
			argv[index++] = argv[jndex];
		jndex++;
	}
	argv[index] = NULL;
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
			if (ft_strchr(lst->argv[i], '$'))
				expand_helper(lst, envp, &i, &tr);
			i++;
		}
		remove_null_values(lst->argv, i);
		lst = lst->next;
	}
}

void	dolar_dolar_case(t_expand *exp, int *j)
{
	char	*temp;

	temp = exp->cmd;
	exp->cmd = ft_strjoin(temp, "\b");
	free(temp);
	(*j) += 2;
}
