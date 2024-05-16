/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:02:46 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/16 14:11:12 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_with_sep(char *s1, char *s2, char sep)
{
	int		i;
	int		j;
	char	*result;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!result)
		return (NULL);
	while (s1[++i])
		result[i] = s1[i];
	result[i] = sep;
	j = i + 1;
	i = -1;
	while (s2[++i])
		result[j + i] = s2[i];
	result[j + i] = '\0';
	return (result);
}

char	*command(char *my_argv, char **envr)
{
	char	**path;
	char	*joiner;
	char	*command_path;
	int		i;

	path = get_path(envr);
	i = 0;
	check(my_argv);
	while (path[i])
	{
		if (access(my_argv, F_OK | X_OK) == 0)
			return (my_argv);
		joiner = ft_strjoin(path[i], "/");
		command_path = ft_strjoin(joiner, my_argv);
		free(joiner);
		if (access(command_path, F_OK | X_OK) == 0)
			return (free_all(path), command_path);
		free(command_path);
		i++;
	}
	return (free_all(path), NULL);
}

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*check(char *my_argv)
{
	if (my_argv[0] == '/')
	{
		if (access(my_argv, F_OK | X_OK) == 0)
			return (my_argv);
		else
		{
			printf("error in acces /\n");
			exit(1);
		}
	}
	return (0);
}

char	**get_path(char **envr)
{
	int		i;
	char	**s;

	i = 0;
	while (envr[i])
	{
		if (!ft_strncmp("PATH=", envr[i], 5))
			break ;
		i++;
	}
	s = ft_split(envr[i] + 5, ':');
	return (s);
}
