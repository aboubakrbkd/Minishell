/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:22:13 by aboukdid          #+#    #+#             */
/*   Updated: 2024/07/20 13:22:35 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_the_delim(char *arg, char *delim)
{
	int	i;
	int	j;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (arg[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (in_single_quote || in_double_quote
			|| (!in_single_quote && !in_double_quote))
			delim[j++] = arg[i];
		i++;
	}
	delim[j] = '\0';
}

char	*get_delimiter(char *arg)
{
	char	*delim;

	delim = malloc(ft_strlen(arg) + 1);
	if (!delim)
		return (NULL);
	check_the_delim(arg, delim);
	return (delim);
}

void	get_delim(t_cmd *lst)
{
	int	i;
	int	k;
	int	delim_size;

	delim_size = get_delim_size(lst) * 2;
	lst->delim = malloc(sizeof(char *) * (delim_size * 2 + 2));
	if (!lst->delim)
		return ;
	i = 0;
	k = 0;
	while (lst->argv[i] && lst->argv[i + 1])
	{
		if (!ft_strcmp(lst->argv[i], "<<"))
		{
			if (ft_strchr(lst->argv[i + 1], '\''))
				lst->is_qoute = 1;
			lst->delim[k] = get_delimiter(lst->argv[i + 1]);
			k++;
		}
		i++;
	}
	lst->delim[k] = NULL;
}
