/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:55:09 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/16 17:33:37 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_delim(char **arg)
{
	int	i;

	i = 0;
	while (arg[++i])
		if (!ft_strcmp(arg[i - 1], "<<"))
			return (arg[i]);
	return (NULL);
}

void	her_sin(int sig)
{
	if (sig == SIGINT)
	{
		ex_st(1, 1);
		close(0);
	}
}

char	*creat_heroc(t_cmd *lst)
{
	int		i;
	char	*tmp;

	i = 0;
	while (++i)
	{
		tmp = ft_strjoin("heredoc", ft_itoa(i));
		if (!tmp)
			return (NULL);
		lst->fd = open(tmp, O_RDONLY, 0644);
		if (lst->fd == -1)
		{
			lst->fd = open(tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (lst->fd < 0)
				return (NULL);
			return (tmp);
		}
	}
	return (NULL);
}

void	perferm_heredoc(t_cmd *lst, char *delim)
{
	char	*exp;
	char	*tmp;

	signal(SIGINT, her_sin);
	while (1)
	{
		tmp = readline("> ");
		if (!ttyname(0))
		{
			open(ttyname(2), O_RDWR);
			return ;
		}
		if (!tmp || ((ft_strncmp(tmp, delim, ft_strlen(delim)) == 0)
				&& (ft_strlen(tmp) == ft_strlen(delim))))
			break ;
		exp = expand_variables(tmp);
		if (exp)
		{
			write(lst->fd, exp, ft_strlen(exp));
			write(lst->fd, "\n", 1);
			free(exp);
		}
		else
		{
			write(lst->fd, tmp, ft_strlen(tmp));
			write(lst->fd, "\n", 1);
			free(tmp);
		}
	}
	free(tmp);
}

void	heredoc(t_cmd *lst)
{
	char	*tmp;

	while (lst)
	{
		lst->delim = get_delim(lst->argv);
		tmp = creat_heroc(lst);
		perferm_heredoc(lst, lst->delim);
		lst->infile = open(tmp, O_RDONLY);
		close(lst->fd);
		unlink(tmp);
		lst = lst->next;
	}
}

int	is_heredoc(t_cmd *lst)
{
	int	i;
	int	res;

	res = 0;
	while (lst)
	{
		i = 0;
		lst->is_heredoc = 0;
		while (lst->argv[i])
		{
			if (ft_strcmp(lst->argv[i], "<<") == 0)
			{
				lst->is_heredoc = 1;
				res = 1;
			}
			i++;
		}
		lst = lst->next;
	}
	return (res);
}
