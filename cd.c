/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:54:47 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/14 21:06:58 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

t_global	g_global;

char	*my_getenv(char *name)
{
	t_env	*env;

	env = g_global.envs;
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(name)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	update_env(char *name, char *value)
{
	t_env	*tmp;

	tmp = g_global.envs;
	if (!name || !value)
		return ;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
		{
			tmp->value = ft_strdup(value);
			break ;
		}
		tmp = tmp->next;
	}
}

void	update_pwd(char *path)
{
	char	*home;

	update_env("OLDPWD", my_getenv("PWD"));
	home = getcwd(NULL, 0);
	update_env("PWD", home);
}


int	cd(char **argv)
{
	int		i;
	char	*home;

	i = 1;
	while (argv[i])
		i++;
	if (i == 1)
	{
		home = my_getenv("HOME");
		if (!home)
			printf("cd: HOME not set\n");
		if (chdir(home) == -1)
			printf("cd: %s: No such file or directory\n", home);
		update_pwd(my_getenv("HOME"));
		return (0);
	}
	else
	{
		if (!strcmp(argv[1], "~"))
		{
			home = my_getenv("HOME");
			if (!home)
				printf("cd: HOME not set\n");
			if (chdir(home) == -1)
				printf("cd: %s: No such file or directory\n", home);
			update_pwd(my_getenv("HOME"));
			return (0);
		}
		else if (!strcmp(argv[1], "-"))
		{
			if (chdir(my_getenv("OLDPWD")) == -1)
				printf("cd: %s: No such file or directory\n", my_getenv("OLDPWD"));
			update_pwd(my_getenv("OLDPWD"));
			printf("%s\n", my_getenv("PWD"));
			return (0);
		}
		else if (chdir(argv[1]) == -1)
		{
			printf("cd: %s: No such file or directory\n", argv[1]);
			return (1);
		}
	}
	update_pwd(argv[1]);
	return (0);
}


// int	cd(char **argv)
// {
// 	int		i;
// 	char	*home;

// 	i = 1;
// 	while (argv[i])
// 		i++;
// 	if (i == 1)
// 	{
// 		home = my_getenv("HOME");
// 		if (!home)
// 			printf("cd: HOME not set\n");
// 		if (chdir(home) == -1)
// 			printf("cd: %s: No such file or directory\n", home);
// 		update_pwd(my_getenv("HOME"));
// 		return (0);
// 	}
// 	else
// 	{
// 		if (chdir(argv[1]) == -1)
// 		{
// 			printf("cd: %s: No such file or directory\n", argv[1]);
// 			return (1);
// 		}
// 	}
// 	update_pwd(argv[1]);
// 	return (0);
// }
