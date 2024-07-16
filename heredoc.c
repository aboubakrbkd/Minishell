/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:55:09 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/16 04:16:59 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_delim(t_cmd *lst)
{
	int	i;
	int	count;

	count = 1;
	while (lst)
	{
		i = 0;
		while (lst->argv[i])
		{
			if (ft_strcmp(lst->argv[i], "<<") == 0)
				count++;
			i++;
		}
		lst = lst->next;
	}
	return (count);
}

int	set_delim(t_cmd *lst, t_heredoc *here)
{
	int	i;
	int	j;

	j = 0;
	here->delimiter = malloc(sizeof(char *) * count_delim(lst) + 1);
	while (lst)
	{
		i = 0;
		while (lst->argv[i])
		{
			if (ft_strcmp(lst->argv[i], "<<") == 0)
			{
				here->delimiter[j] = ft_strdup(lst->argv[i + 1]);
				j++;
			}
			here->delimiter[j] = NULL;
			i++;
		}
		lst = lst->next;
	}
	return (j);
}

int	heredoc(t_cmd *lst, t_heredoc *here)
{
	char	*tmp;
	char	*exp;
	char	*to_open;
	int		i;
	int		fd;

	fake(here);
	i = 0;
	while (++i)
	{
		to_open = ft_strjoin("heredoc", ft_itoa(i));
		fd = open(to_open, O_RDONLY, 0644);
		if (fd == -1)
		{
			fd = open(to_open, O_RDWR| O_CREAT | O_TRUNC, 0644);
			break ;
		}
		else if (fd > 0)
			continue ;
	}
	while (1)
	{
		tmp = readline("> ");
		if (!tmp || ((ft_strncmp(tmp, here->delimiter[here->idx] 
				,ft_strlen(here->delimiter[here->idx])) == 0)
				&& (ft_strlen(tmp) == ft_strlen(here->delimiter[here->idx]))))
			break ;
		exp = expand_variables(tmp);
		if (exp)
		{
			write(fd, exp, ft_strlen(exp));
			write(fd, "\n", 1);
			free(exp);
		}
		else
		{
			write(fd, tmp, ft_strlen(tmp));
			write(fd, "\n", 1);
			free(tmp);
		}
	}
	if (here->delimiter[here->idx][0] == '\n')
		free(here->delimiter[here->idx]);
	free(tmp);
	while (lst->next)
		lst = lst->next;
	lst->infile = open(to_open, O_RDONLY);
	close(fd);
	unlink(to_open);
	if (lst->infile < 0)
		return (1);
	return (0);
}

void	fake(t_heredoc *here)
{
	char	*tmp;
	int		i;

	i = 0;	
	while (here->delimiter[i + 1])
	{
		while (1)
		{
			tmp = readline("> ");
			if (!tmp || ((ft_strncmp(tmp, here->delimiter[i], ft_strlen(here->delimiter[i])) == 0)
					&& (ft_strlen(tmp) == ft_strlen(here->delimiter[i]))))
					break ;
			free(tmp);
		}
		i++;
	}
}

int	is_heredoc(t_cmd *lst, t_heredoc *here)
{
	int	i;

	while (lst)
	{
		i = 0;
		lst->is_heredoc = 0;
		while (lst->argv[i])
		{
			if (ft_strcmp(lst->argv[i], "<<") == 0)
			{
				lst->is_heredoc = 1;
				here->idx = set_delim(lst, here) - 1;
				return (1);
			}
			i++;
		}
		lst = lst->next;
	}
	return (0);
}
