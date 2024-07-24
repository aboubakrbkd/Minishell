/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:53 by aboukdid          #+#    #+#             */
/*   Updated: 2024/07/24 23:48:46 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*build_arr(char **res)
{
	t_cmd	*head;
	int		i;

	head = NULL;
	i = 0;
	while (res[i])
	{
		add_back(&head, ft_new(res[i]));
		i++;
	}
	return (free_all(res), head);
}

void	remove_quotes_from_arg(char *arg)
{
	int		i;
	int		j;
	int		tr;
	char	qoutes;

	if (count_single(arg) == 1 && count_double(arg) == 0)
		return  ;
	i = -1;
	j = 0;
	tr = 0;
	while (arg[++i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			qoutes = arg[i], tr = 1;
			break ;
		}
	}
	i = -1;
	while (++i < ft_strlen(arg))
	{
		if (arg[i] == qoutes && tr == 1)
		{
			tr = 0;
			continue ;
		}
		if (arg[i] != qoutes)
			arg[j++] = arg[i];
	}
	arg[j] = '\0';
}

void	process_argv(char **argv)
{
	while (*argv != NULL)
	{
		remove_quotes_from_arg(*argv);
		argv++;
	}
}

void	remove_qoutes(t_cmd **lst)
{
	t_cmd	*current;

	current = *lst;
	while (current != NULL)
	{
		process_argv(current->argv);
		current = current->next;
	}
}
